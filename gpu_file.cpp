#include <sycl.hpp>
#include "oneapi/mkl/blas.hpp"

using fp = float;

static sycl::device D;
static sycl::context C;
static sycl::queue Q;

void onemkl_device_setup(int device_id) {
  sycl::platform P{sycl::gpu_selector_v};
  D = P.get_devices(sycl::info::device_type::gpu)[device_id];
  C = sycl::context{D};
  Q = sycl::queue{C, D};
}

void onemkl_device_sgemv() {
  oneapi::mkl::transpose transA = oneapi::mkl::transpose::trans;

  // matrix data sizes
  int m = 79;
  int n = 83;

  // leading dimension of data
  int ldA = 103;

  // increment for x and y
  int incx = 1;
  int incy = 1;

  // set scalar fp values
  fp alpha = 2.0;
  fp beta  = 3.0;

  // prepare matrix data
  std::vector<fp> A(m*n);

  // prepare vector data
  std::vector<fp> x(n);
  std::vector<fp> y(m);

  sycl::buffer<fp, 1> A_buffer(A.data(), A.size());
  sycl::buffer<fp, 1> x_buffer(x.data(), x.size());
  sycl::buffer<fp, 1> y_buffer(y.data(), y.size());

  // add oneapi::mkl::blas::gemv to execution queue
  try {
    oneapi::mkl::blas::gemv(Q, transA, m, n, alpha, A_buffer, ldA, x_buffer, incx, beta, y_buffer, incy);
  }
  catch(sycl::exception const& e) {
    std::cout << "\t\tCaught synchronous SYCL exception during GEMV:\n"
              << e.what() << std::endl << "OpenCL status: " << e.code().value() << std::endl;
  }
}

int main(int argc, char *argv[]) {
  onemkl_device_setup(0);
  onemkl_device_sgemv();
  return 0;
}
