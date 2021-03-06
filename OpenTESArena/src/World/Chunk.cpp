#include "Chunk.h"

Chunk::Chunk(const Voxel &fillVoxel)
{
	// Set all of this chunk's voxels to the given voxel.
	for (auto &voxel : this->voxels)
	{
		voxel = fillVoxel;
	}
}

Chunk::Chunk()
{

}

Chunk::~Chunk()
{

}

const Voxel &Chunk::get(int x, int y, int z)
{
	return this->voxels.at(x + (y * Chunk::Width) +
		(z * Chunk::Width * Chunk::Height));
}

void Chunk::set(int x, int y, int z, const Voxel &voxel)
{
	this->voxels.at(x + (y * Chunk::Width) +
		(z * Chunk::Width * Chunk::Height)) = voxel;
}
