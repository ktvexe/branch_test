# Summary

* This is a simple branch prediction performance test
* Use the likely, unlikely macro and bitwise


# Build
* `$ make`

# Result of branch misses
```
Performance counter stats for './branch_normal' (50 runs):

             8,353      branch-misses             #    3.39% of all branches          ( +-  0.99% )
           246,298      branch-instructions                                           ( +-  0.15% )

       0.000860847 seconds time elapsed                                          ( +-  4.97% )

Performance counter stats for './branch_unlikely' (50 runs):

             8,184      branch-misses             #    3.33% of all branches          ( +-  0.84% )
           245,538      branch-instructions                                           ( +-  0.12% )

       0.000787099 seconds time elapsed                                          ( +-  3.46% )

Performance counter stats for './branch_likely' (50 runs):

             8,064      branch-misses             #    3.28% of all branches          ( +-  0.75% )
           245,992      branch-instructions                                           ( +-  0.14% )

       0.000583797 seconds time elapsed                                          ( +-  4.82% )

Performance counter stats for './branch_bitwise' (50 runs):

             5,735      branch-misses             #    2.49% of all branches          ( +-  1.50% )
           230,256      branch-instructions                                           ( +-  0.16% )

       0.000605876 seconds time elapsed                                          ( +-  7.00% )

```

## Result of execution time
```
./branch_normal 
DONE 248694

./branch_likely 
DONE 323975

./branch_unlikely 
DONE 326667

./branch_bitwise 
DONE 50069

```
# License
`branch_test` is freely redistributable under the two-clause BSD License.
Use of this source code is governed by a BSD-style license that can be found
in the `LICENSE` file.
