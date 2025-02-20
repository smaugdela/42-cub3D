# 42-cub3D

## Goal
The second graphical project from 42. We have to create a game using a ray-casting algorithm, inspired by the infamous Wolfenstein 3D (1992), one of the first 3d fps game ever.

## Mandatory Instructions
- Your project must be written in C.
- Your project must be written in accordance with the Norm. If you have bonus
files/functions, they are included in the norm check and you will receive a 0 if there
is a norm error inside.
- Your functions should not quit unexpectedly (segmentation fault, bus error, double
free, etc) apart from undefined behaviors. If this happens, your project will be
considered non functional and will receive a 0 during the evaluation.
- All heap allocated memory space must be properly freed when necessary. No leaks
will be tolerated.
- If the subject requires it, you must submit a Makefile which will compile your
source files to the required output with the flags -Wall, -Wextra and -Werror, use
cc, and your Makefile must not relink.
- Your Makefile must at least contain the rules $(NAME), all, clean, fclean and
re.
- To turn in bonuses to your project, you must include a rule bonus to your Makefile,
which will add all the various headers, librairies or functions that are forbidden on
the main part of the project. Bonuses must be in a different file _bonus.{c/h}.
Mandatory and bonus part evaluation is done separately.
- If your project allows you to use your libft, you must copy its sources and its
associated Makefile in a libft folder with its associated Makefile. Your project’s
Makefile must compile the library by using its Makefile, then compile the project.
- We encourage you to create test programs for your project even though this work
won’t have to be submitted and won’t be graded. It will give you a chance
to easily test your work and your peers’ work. You will find those tests especially
useful during your defence. Indeed, during defence, you are free to use your tests
and/or the tests of the peer you are evaluating.
- Submit your work to your assigned git repository. Only the work in the git repository will be graded. If Deepthought is assigned to grade your work, it will be done
after your peer-evaluations. If an error happens in any section of your work during
Deepthought’s grading, the evaluation will stop.

## How to Use
Clone the repository in the location of your choice, go inside it, then compile using make bonus command:
```
cd 42-cub3D
make bonus
```
You can then launch the program using ./cub3D_bonus, and the path of the map (.cub file) you want to play on:
```
./cub3D_bonus <*.cub>
```
If you want to modify the map, you just have to edit the .cub map located in the following path: ```/assets/maps/maps_bonus/```. Here are the two main maps made to be played:
```
./cub3D_bonus assets/maps/maps_bonus/sasageyo.cub 
```
and
```
./cub3D_bonus assets/maps/maps_bonus/alien.cub  
```

## Pictures

![cub3d_door](https://github.com/user-attachments/assets/2104c3d6-e18e-4110-b3bd-e5cc46068c6a)
![cub3d_babies](https://github.com/user-attachments/assets/3a12099b-dad7-4c98-b594-a453f6a9e461)
![cub3d_xenomorph](https://github.com/user-attachments/assets/591a61a9-1b80-481d-b33d-6f41b0c90076)

Enjoy!
