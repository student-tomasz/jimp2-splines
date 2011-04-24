#\[ee\]\[jimp2\] Interpolation with cubic splines

## Get

    git clone git@github.com:student-tomasz/jimp2-splines.git cudzilot_splines/
    cd cudzilot_splines/src/
    rake
    cd ..

## Use

    ./spline [flags] [-o|--out output_filename] input_filename
    ./spline [flags] -o|--out output_filename < input_filename

## Y U NO HAVE CLEAN CODE?!
Some fixes and todos that should be applied:

* `io` 
  * make `io_log()` a normal function, not some hax0r macro
  * make `io_log()` accept any number of arguments, just like printf()
  * it would be really nice if `io` function could use templates instead of
    keeping text inside code
  * `MAX_STR_LENGTH` is fucking ugly

* `cli`
  * joined flags like `./spline -qfgo asd.out` should be accepted

* `options`
  * global `struct options` sucks

* `matrix`
  * rewrite `matrix_t` so it doesn't store all those `0`s
  * maybe gaussian elimination can be faster?

![SRSLY!!! Y U NO CLEAN?!](http://i.imgur.com/nmMXd.jpg)

