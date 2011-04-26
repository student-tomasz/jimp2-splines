# Interpolation using cubic splines

## Get

    git clone git@github.com:student-tomasz/jimp2-splines.git cudzilot_splines/
    cd cudzilot_splines/
    rake
    cd build/

## Use

    ./spline [flags] [-o|--out output_filename] input_filename
    ./spline [flags] -o|--out output_filename < input_filename

## Y U NO HAVE CLEAN CODE?!
Some fixes and todos that should be applied:

* `cli`
  * joined flags like `./spline -qfgo asd.out` should be accepted

* `options`
  * global `options` sucks

* `matrix`
  * rewrite `matrix_t` so it doesn't store all those `0`s
  * gaussian elimination should be faster, it chokes at 1k points

![SRSLY!!! Y U NO CLEAN?!](http://i.imgur.com/nmMXd.jpg)

