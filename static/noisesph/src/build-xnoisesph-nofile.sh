# clean
rm -f ./xnoisesph-nofile.out
#build
gcc -Wall -Wno-pointer-sign -g xnoisesph-nofile.c -o xnoisesph-nofile.out -L/usr/lib/x86_64-linux-gnu -lX11 -lm

# cc prog.c -o prog -L/usr/X11/lib -lX11
#run
./xnoisesph-nofile.out

