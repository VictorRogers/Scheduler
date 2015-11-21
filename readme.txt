Notice: This project is made with the GNU Compiler Collection (GCC).
        LCC is still not available to install on any of the school machines,
        but GCC is available on every student accessible computer in the
        university by using the Cygwin program.

Cygwin can be accessed from either the desktop or the CS folder on any
university computer.

To utilize GCC via Cygwin, the project folder "Scheduler" must be placed
in the C:\cygwin64\home\username directory.

The project directory is like so

Scheduler
|
|__source
|  |
|  |__fcfs
|  |  |
|  |  |__header
|  |  |__input
|  |  |  |__input.txt (please place input data here in this file)
|  |  |__object
|  |  |__output
|  |  |  |__output.txt (this file will generate with output after running program)
|  |  |src
|  |Makefile

This setup is identical for all other programs (rr, sjf, hpf).

- Making programs -
From the "Scheduler" directory, to build fcfs, simply cd to the fcfs directory and
type make. At this point, GCC will compile the fcfs program with all warnings and
running strict c99 standard. To run the program, simply type "./fcfs". The output
will be generated in the output directory. To remove the executable, object files,
and the output file, simply type "make clean".

cd source/fcfs
make
./fcfs
make clean

This same process works for all of the four programs


