//----------------------------------------------------------------------------------------------------

#include "MD2.hpp"

#include <cstdint>
#include <stdexcept>
#include <iostream>
//----------------------------------------------------------------------------------------------------

namespace
{
//----------------------------------------------------------------------------------------------------

using namespace MD2View;
//----------------------------------------------------------------------------------------------------

constexpr std::int32_t md2Ident = (('2'<<24) + ('P'<<16) + ('D'<<8) + 'I');
constexpr std::int32_t md2Version = 8;
//----------------------------------------------------------------------------------------------------

struct MD2Header
{
	std::int32_t ident;             // magic number. must be equal to "IDP2"
	std::int32_t version;           // md2 version. must be equal to 8

	std::int32_t skinWidth;         // width of the texture
	std::int32_t skinHeight;        // height of the texture
	std::int32_t frameSize;         // size of one frame in bytes

	std::int32_t numSkins;          // number of textures
	std::int32_t numVertices;       // number of vertices
	std::int32_t numSt;             // number of texture coordinates
	std::int32_t numTris;           // number of triangles
	std::int32_t numGlcmds;         // number of opengl commands
	std::int32_t numFrames;         // total number of frames

	std::int32_t ofsSkins;          // offset to skin names (64 bytes each)
	std::int32_t ofsSt;             // offset to s-t texture coordinates
	std::int32_t ofsTris;           // offset to triangles
	std::int32_t ofsFrames;         // offset to frame data
	std::int32_t ofsGlcmds;         // offset to opengl commands
	std::int32_t ofsEnd;            // offset to end of file
};
//----------------------------------------------------------------------------------------------------

typedef float MD2Vector3[3];
//----------------------------------------------------------------------------------------------------

static MD2Vector3 anorms[] = {
#include "anorms.h"
};
//----------------------------------------------------------------------------------------------------

struct MD2Skin
{
	char name[64];
};
//----------------------------------------------------------------------------------------------------

struct MD2TexCoord
{
	std::int16_t s;
	std::int16_t t;
};
//----------------------------------------------------------------------------------------------------

struct MD2Triangle
{
	std::uint16_t vertex[3]; // vertex indices
	std::uint16_t st[3]; // tex. coord. indices
};
//----------------------------------------------------------------------------------------------------

struct MD2Vertex
{
	std::uint8_t v[3]; // position (compressed)
	std::uint8_t normalIdx; // normal index
};
//----------------------------------------------------------------------------------------------------

struct MD2Frame
{
	MD2Vector3 scale;
	MD2Vector3 translate;
	char name[16];
//	MD2Vertex* verts;
};
//----------------------------------------------------------------------------------------------------

} // namespace
//----------------------------------------------------------------------------------------------------

namespace MD2View
{
//----------------------------------------------------------------------------------------------------

std::istream& operator>>(std::istream& stream, MD2& m)
{
	MD2Header header;

	stream.read((char *)&header, sizeof(header));

	if ((header.ident != md2Ident) || (header.version != md2Version))
		throw std::logic_error("wrong file format!");

	m.indices.clear();
	m.indices.reserve(header.numTris * 3);

	std::vector<MD2Triangle> triangles(header.numTris, MD2Triangle());

	stream.seekg(header.ofsTris, std::ios::beg);
	stream.read((char *)triangles.data(), sizeof(MD2Triangle) * header.numTris);

	for (const MD2Triangle& tri : triangles)
	{
		m.indices.push_back(tri.vertex[0]);
		m.indices.push_back(tri.vertex[1]);
		m.indices.push_back(tri.vertex[2]);
	}

	m.triangles = header.numTris;

	m.data.clear();

	std::vector<MD2Vertex> buff(header.numVertices, MD2Vertex());
	std::vector<float> normals;

	m.data.reserve(header.numFrames * header.numVertices * 3 * 2);
	normals.reserve(header.numFrames * header.numVertices * 3);

	stream.seekg(header.ofsFrames, std::ios::beg);

	for (int i = 0; i < header.numFrames; ++i)
	{
		MD2Frame frame;

		stream.read((char *)&frame, sizeof(MD2Frame));
		stream.read((char *)buff.data(), header.numVertices * sizeof(MD2Vertex));

		for (MD2Vertex& v: buff)
		{
			m.data.push_back(frame.scale[0] * v.v[0] + frame.translate[0]);
			m.data.push_back(frame.scale[2] * v.v[2] + frame.translate[2]);
			m.data.push_back(frame.scale[1] * v.v[1] + frame.translate[1]);

			normals.push_back(anorms[v.normalIdx][0]);
			normals.push_back(anorms[v.normalIdx][2]);
			normals.push_back(anorms[v.normalIdx][1]);
		}
	}

	m.data.insert(m.data.end(), normals.begin(), normals.end());
	m.vertices = header.numVertices;
	m.frames = header.numFrames;

	stream.seekg(header.ofsEnd, std::ios::beg);

	return stream;
}
//----------------------------------------------------------------------------------------------------

bool MD2::empty() const
{
	return data.empty();
}
//----------------------------------------------------------------------------------------------------

} // namespace MD2View
//----------------------------------------------------------------------------------------------------
