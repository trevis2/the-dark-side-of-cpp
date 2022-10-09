<h1/>Makefiles usage description </h1>

Make is Unix utility that is designed to start execution of a makefile. A makefile is a special file, containing shell commands, that you create and name makefile (or Makefile depending upon the system). While in the directory containing this makefile, you will type make and the commands in the makefile will be executed. If you create more than one makefile, be certain you are in the correct directory before typing make. Makefile defines set of tasks to be executed

<h4/>Easiest Makefile description:</h4>

Create a empty directory myproject containing a file Makefile with this content:

  say_hello:
          echo "Hello World"

Now run the file by typing make inside the directory myproject. The output will be:

  $ make
  echo "Hello World"
  Hello World        
In the example above, say_hello behaves like a function name, as in any programming language. This is called the target. The prerequisites or dependencies follow the target. For the sake of simplicity, we have not defined any prerequisites in this example. The command echo "Hello World" is called the recipe. The recipe uses prerequisites to make a target. The target, prerequisites, and recipes together make a rule.

To summarize, below is the syntax of a typical rule:

  target: prerequisites
  <TAB> recipe

Going back to the example above, when make was executed, the entire command echo "Hello World" was displayed, followed by actual command output. We often don't want that. To suppress echoing the actual command, we need to start echo with @:

say_hello:
        @echo "Hello World"

Now try to run make again. The output should display only this:

$ make
Hello World

As an example, a target might be a binary file that depends on prerequisites (source files). On the other hand, a prerequisite can also be a target that depends on other dependencies:

  final_target: sub_target final_target.c
          Recipe_to_create_final_target

  sub_target: sub_target.c

  Recipe_to_create_sub_target


Let's add a few more phony targets: generate and clean to the Makefile:

say_hello:
        @echo "Hello World"

generate:
        @echo "Creating empty text files..."
        touch file-{1..10}.txt

clean:
        @echo "Cleaning up..."
        rm *.txt

        Let's add a few more phony targets: generate and clean to the Makefile:

say_hello:
      @echo "Hello World"

generate:
      @echo "Creating empty text files..."
      touch file-{1..10}.txt

clean:
      @echo "Cleaning up..."
      rm *.txt
