# simple_c_opencl
Add two arrays using parallel computation with OpenCL (OCL)

`kernel` - an OCL function
`context` - current system configuration (OS, types and amounts of devices)

### Template kernel functions

`get_cl_kernel` - setup kernel: allocate memory buffers, assign buffers as kernel arguments, create and build OCL program, set OCL kernel from source file.
`execute_kernel` - load data in kernel buffers (arguments) and execute kernel.
`clean_kernel` - free ('release') kernel buffers and kernel itself.

### Template context functions

`get_cl_context` - setup context: get available platform and devices, save them into context and create queue.
`clean_context` - free ('release') queue and context

### Template kernel source file

`vector_add_kernel.cl` - source file containing an OCL function

## Usage

    clone
    cd repository
    make
    ./simple_opencl vector_add_kernel.cl
