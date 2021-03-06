/*
Copyright 2017 Jiawei Chiu

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/
#include "impute.h"
#include "base.h"

DEFINE_string(output_filename, "", "Output file for stats.");

DEFINE_string(train_filename, "", "Filename for training dataset.");
DEFINE_string(train_t_filename, "",
              "Filename for training dataset, transposed.");
DEFINE_string(test_filename, "", "Filename for training dataset.");
DEFINE_string(train_perm_filename, "",
              "Filename for training data permutation.");

DEFINE_bool(use_gpu, true,
            "Use GPU for our computations. If false, we use CPU only.");

DEFINE_int32(
    k, 32,
    "Number of singular values computed per iteration. Should be powers of 2.");

DEFINE_double(sv_threshold, 10.0, "Singular value threshold.");

DEFINE_int32(num_gram, 1,
             "Apply Gram matrix this many times. Recommend either 0 or 1.");

DEFINE_int32(log_every_sec, 3, "Log / evaluate every this many seconds.");

DEFINE_string(init, "zero",
              "How to initialize U and V? Possibilities: zero, rand");

DEFINE_double(max_time, 100000, "Maximum time in seconds.");

DEFINE_int32(
    randn, 1000000,
    "SVD is computed by applying A to a random matrix. We often reuse this "
    "matrix from the previous iteration. Every this many iterations, we will "
    "re-initialize this random matrix.");

DEFINE_bool(soft_threshold, true, "Soft threshold? Otherwise, hard threshold.");

DEFINE_bool(randomize_init, false, "Randomize the initial solution?");

DEFINE_bool(accelerated, true, "Use accelerated version?");

DEFINE_int32(rng_seed, 3255245, "Seed for rng.");

DEFINE_int32(
    randn_iters, 20,
    "Regenerate test matrix for randomized SVD every this many iterations.");

namespace gi {

void Main() {
  EngineOptions e_opt;
  e_opt.rng_seed = FLAGS_rng_seed;
  Engine engine(e_opt);
  ImputeOptions opt;
  opt.output_filename = FLAGS_output_filename;
  opt.train_filename = FLAGS_train_filename;
  opt.train_t_filename = FLAGS_train_t_filename;
  opt.test_filename = FLAGS_test_filename;
  opt.train_perm_filename = FLAGS_train_perm_filename;

  opt.sv_threshold = FLAGS_sv_threshold;
  opt.k = FLAGS_k;
  opt.num_gram = FLAGS_num_gram;
  opt.use_gpu = FLAGS_use_gpu;
  opt.randomize_init = FLAGS_randomize_init;
  opt.log_every_sec = FLAGS_log_every_sec;
  opt.max_time = FLAGS_max_time;
  opt.soft_threshold = FLAGS_soft_threshold;
  opt.accelerated = FLAGS_accelerated;
  opt.randn_iters = FLAGS_randn_iters;

  Impute impute(opt);
  impute.Run();
}

} // namespace gi

int main(int argc, char **argv) {
  gi::MainInit(argc, argv);
  gi::Main();
}
