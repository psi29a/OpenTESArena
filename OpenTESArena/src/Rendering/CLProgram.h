#ifndef CL_PROGRAM_H
#define CL_PROGRAM_H

#include <vector>

#define CL_HPP_MINIMUM_OPENCL_VERSION 120
#define CL_HPP_TARGET_OPENCL_VERSION 120
#define CL_USE_DEPRECATED_OPENCL_1_2_APIS
#include <CL/cl2.hpp>

#include "../Math/Float3.h"

// The OpenCL object should be kept alive while the game data object is alive.
// Otherwise, it would reload the kernel whenever the game world panel was
// re-entered, which is unnecessary. Therefore, this object should be kept in
// the game data object.

// It is important to remember that cl_float3 and cl_float4 are structurally
// equivalent.

struct SDL_Surface;

class CLProgram
{
private:
	static const std::string PATH;
	static const std::string FILENAME;
	static const std::string TEST_KERNEL;
	static const std::string INTERSECT_KERNEL;
	static const std::string AMBIENT_OCCLUSION_KERNEL;
	static const std::string RAY_TRACE_KERNEL;
	static const std::string ANTI_ALIAS_KERNEL;
	static const std::string POST_PROCESS_KERNEL;
	static const std::string CONVERT_TO_RGB_KERNEL;

	static const cl::size_type SIZEOF_CAMERA;

	cl::Device device; // The device selected from the devices list.
	cl::Context context;
	cl::CommandQueue commandQueue;
	cl::Program program;
	cl::Kernel kernel;
	cl::Buffer cameraBuffer, gameTimeBuffer, outputBuffer;
	int width, height;

	std::string getBuildReport() const;
	std::string getErrorString(cl_int error) const;
public:
	// Constructor for the OpenCL render program.
	CLProgram(int width, int height);
	~CLProgram();

	// These are public in case the options menu is going to need to list them.
	// There should be a constructor that also takes a platform and device, then.
	static std::vector<cl::Platform> getPlatforms();
	static std::vector<cl::Device> getDevices(const cl::Platform &platform,
		cl_device_type type);

	void updateCamera(const Float3d &eye, const Float3d &direction, double fovY);

	// Give this method total ticks instead of delta time so the constructor doesn't
	// need a "start time". Also, this prevents any additive "double -> float" error.
	void updateGameTime(double gameTime);

	void render(SDL_Surface *dst);
};

#endif
