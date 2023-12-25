#!/usr/bin/bash
################################################################################
#                                    kaveh
################################################################################
# There's a __project.sh__ at the root. load it first: `. project.sh`
#
# tools:
# static code analyzer:
#   - c: splint, cppcheck
# memory debugger: valgrind
# system call tracer: strace
# display info about .obj files: objdump
#
# opening/editing files: noevim
#   folding/unfolding: z Shift+m, z Shift+r
#   switch between source/header: F2
#
# lookup refrences: lsp, ctags
# find/replace in single file: neovim
# find/replace in whole project: ambr <source_text> <dest_text>
# find files: ctrl-t | ff <file-name> | fzf | fd
# find string/text in single file: neovim (/)
# find string/text in whole project: ft <text> | rg <text>
# find docs of c standard librariy: 
#   - install man-pages-devel and man <method>
#   - zeal
#   - www.devdocs.io 
#
# debuggers: gf2, gdb
################################################################################
app=""
compiler="cc"
flags="-Wall -Wextra -Wpedantic -Wformat=2 -Wno-unused-parameter -Wshadow 
  -Wwrite-strings -Wstrict-prototypes -Wold-style-definition -Wredundant-decls
  -Wnested-externs -Wmissing-include-dirs
  -Wjump-misses-init -Wlogical-op"
src="src/*.c"

mode="debug"
build_dir="build/$mode"

mode_flags=""
if [ "$mode" == "debug" ]; then
  app="kaveh"
  mode_flags="-g -O0"
fi

if [ "$mode" == "release" ]; then
  app="kaveh"
  mode_flags="-O3 -DRELEASE"
fi

if [ "$mode" == "test" ]; then
  app="kaveh_test"
fi

_generateTags() {
  echo ">>> generating tags"
  ctags --fields=+iaSl --extras=+q --extras=+f --sort=yes -R src/*
}

p() {
  commands=("build" "debug" "run" "build type" "clean" "generate tags"
    "search" "search/replace"
    "linter - splint" "linter - cppcheck" "valgrind"
    "nm - list symbols from object files" "ldd - print shared object dependencies"
    "objdump -S: Intermix source code with disassembly"
    "objdump -g: Display debug information in object file"
    "objdump -d: Display assembler contents of executable sections"
    "readelf -h: Display the ELF file header"
    "readelf -s:Display the symbol table"
    "readelf -d: Display the dynamic section (if present)"
    "strace - trace system calls and signals"
    "strace -c: Count time, calls, and errors for each system call"
    "ltrace: trace library calls"
    "strings - print the sequences of printable characters in files"
    "size - list section sizes and total size of binary files")
  selected=$(printf '%s\n' "${commands[@]}" | fzf --header="project:")

  case $selected in
    "build")
      clear
      echo ">>> Creating '$build_dir' directory"
      mkdir -p "$build_dir"
      _generateTags
      echo ">>> Compiling ($mode)"
      $compiler $mode_flags $flags -o $build_dir/$app $src
      ;;
    "debug")
      echo ">>> Debugging $app - $mode"
      selected=$(/bin/ls ./tests/ -p | fzf --header="files:")
      gf2 --args ./$build_dir/$app ./tests/$selected &
      ;;
    "run")
      echo ">>> Running $app - $mode"
      selected=$(/bin/ls ./tests/ -p | fzf --header="files:")
      ./$build_dir/$app ./tests/$selected
      ;;
    "build type")
      build_types=("debug" "release")
      build_type_selected=$(printf '%s\n' "${build_types[@]}" | fzf --header="build type:")

      case $build_type_selected in
        "debug")
          sed -i '38,40s/mode="release"/mode="debug"/' project.sh
          source ./project.sh;;
        "release")
          sed -i '38,40s/mode="debug"/mode="release"/' project.sh
          source ./project.sh;;
        *) ;;
      esac
      ;;
    "clean")
      clear
      echo ">>> Cleaning '$build_dir' directory"
      rm -r "$build_dir";;
    "generate tags")
      clear
      _generateTags;;

    "search")
      clear
      read -p "keyword: " p_keyword; rg "$p_keyword" ;;
    "search/replace")
      clear
      read -p "to_search: " to_search
      read -p "to_replace: " to_replace
      ambr "$to_search" "$to_replace" ;;

    "linter - splint")
      clear
      splint +trytorecover src/*;;
    "linter - cppcheck")
      clear
      cppcheck --enable=all --inconclusive --suppress=missingIncludeSystem --language=c src/;;
    "valgrind")
      clear
      valgrind --leak-check=full --show-leak-kinds=all -s -v $build_dir/$app;; #src/*

    "nm - list symbols from object files")
      clear
      nm $build_dir/$app;;
    "ldd - print shared object dependencies")
      clear
      ldd $build_dir/$app;;
    "objdump -S: Intermix source code with disassembly")
      clear
      objdump ./$build_dir/$app -S | less ;;
    "objdump -g: Display debug information in object file")
      clear
      objdump ./$build_dir/$app -g | less;;
    "objdump -d: Display assembler contents of executable sections")
      clear
      objdump ./$build_dir/$app -d | less;;
    "readelf -h: Display the ELF file header")
      clear
      readelf ./$build_dir/$app -h;;
    "readelf -s:Display the symbol table")
      clear
      readelf ./$build_dir/$app -s;;
    "readelf -d: Display the dynamic section (if present)")
      clear
      readelf ./$build_dir/$app -d;;
    "strace - trace system calls and signals")
      clear
      selected=$(/bin/ls ./tests/ -p | fzf --header="files:")
      strace ./$build_dir/$app ./tests/$selected ;;
    "strace -c: Count time, calls, and errors for each system call")
      clear
      selected=$(/bin/ls ./tests/ -p | fzf --header="files:")
      strace -c ./$build_dir/$app ./tests/$selected ;;
    "ltrace: trace library calls")
      clear
      selected=$(/bin/ls ./tests/ -p | fzf --header="files:")
      ltrace ./$build_dir/$app ./tests/$selected ;;
    "strings - print the sequences of printable characters in files")
      clear
      strings $build_dir/$app ;;
    "size - list section sizes and total size of binary files")
      clear
      size $build_dir/$app ;;
    *) ;;
  esac
}
