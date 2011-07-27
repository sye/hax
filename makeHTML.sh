#! /bin/bash
# script to make every cpp/h file to html
find . -iname "*.cpp" -exec vim {} -c TOhtml -c wq -c q \; #render them .cpp
find . -iname "*.h" -exec vim {} -c TOhtml -c wq -c q \; #render them .h

cd ~/public_html/cprog/lab3
rm -f *.html #clean the old files

cd ~/cprog10/lab3/hax
find . -iname "*.html" -exec mv {} ~/public_html/cprog/lab3 \; #copy them to homepage
