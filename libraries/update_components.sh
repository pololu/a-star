# This is a script helps us copy all of the library files we need from
# other repositories and to keep track of what versions were copied.

LIBDIR=AStar32U4Prime
KEYWORDS=$LIBDIR/keywords.txt
COMPONENT_VERSIONS=components.txt

echo > $COMPONENT_VERSIONS
cat $LIBDIR/local_keywords.txt > $KEYWORDS

copylib()
{
  local origin=$1
  shift

  local dir=$1
  shift

  (cd $dir && git diff --quiet) || {
    echo "error: uncommitted changes in $dir"
    return
  }

  echo Copying from $dir

  # Copy the code files.
  until [ -z "$1" ]
  do
    cp $dir/$1 $LIBDIR
    shift
  done

  # Copy the keywords.
  (cat $dir/keywords.txt; echo) >> $KEYWORDS

  # Add an entry to components.txt.
  local ver=`cd $dir && git describe --tags`
  echo $origin $ver >> $COMPONENT_VERSIONS
}

copylib https://github.com/pololu/fastgpio-arduino ../../fastgpio-arduino/FastGPIO FastGPIO.h
copylib https://github.com/pololu/pololu-buzzer-arduino ../../pololu-buzzer-arduino/PololuBuzzer PololuBuzzer{.cpp,.h}
copylib https://github.com/pololu/usb-pause-arduino ../../usb-pause-arduino/USBPause USBPause.h
copylib https://github.com/pololu/pololu-hd44780-arduino ../../pololu-hd44780-arduino/PololuHD44780 PololuHD44780{.cpp,.h}
copylib https://github.com/pololu/pushbutton-arduino ../../pushbutton-arduino/Pushbutton Pushbutton{.cpp,.h}
