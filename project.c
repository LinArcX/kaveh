#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>

const char *app = NULL;
const char *mode = NULL;
const char *build_dir = NULL;
const char *compiler = "cc";
const char *flags = "-lm";
const char *src = "src/*.c";

void createBuildDir() 
{
  printf(">>> Creating '%s' directory\n", build_dir);
  char command[256];
  snprintf(command, sizeof(command), "mkdir -p %s", build_dir);
  system(command);
}

void generateTags() 
{
  printf(">>> Generating tags\n");
  system("ctags --fields=+iaS --extras=+q --extras=+f -R src/*");
}

void compile() 
{
  printf(">>> Compiling (%s)\n", mode);
  char compile_command[256];
  if(0 == strcmp(mode, "debug"))
  {
    snprintf(compile_command, sizeof(compile_command), "%s %s -g -o %s/%s %s", compiler, flags, build_dir, app, src);
  }
  else if (0 == strcmp(mode, "release"))
  {
    snprintf(compile_command, sizeof(compile_command), "%s %s -o %s/%s %s", compiler, flags, build_dir, app, src);
  }
  else 
  {
    printf("unknown mode!");
  }
  system(compile_command);
}

void build() 
{
  createBuildDir();
  generateTags();
  compile();
}

void debug() 
{
  printf(">>> Debugging (%s)\n", app);
  chdir(build_dir);

  // Get the selected test file using ls and fzf (you may need to install fzf)
  char debug_command[256];
  snprintf(debug_command, sizeof(debug_command), "/bin/ls ../../tests/ -p | grep -v / | fzf --header=\"files:\"");
  FILE *fp = popen(debug_command, "r");
  char selected[256];
  if (fgets(selected, sizeof(selected), fp) != NULL) 
  {
    // Launch the debugger (you may need to replace seergdb with your preferred debugger)
    snprintf(debug_command, sizeof(debug_command), "gdb -s %s ../../tests/%s", app, selected);
    system(debug_command);
  }
  pclose(fp);
  chdir("../..");
}

void run() 
{
  printf(">>> Running %s - %s\n", app, mode);
  chdir(build_dir);

  // Get the selected test file using ls and fzf (you may need to install fzf)
  char run_command[256];
  snprintf(run_command, sizeof(run_command), "/bin/ls ../../tests/ -p | grep -v / | fzf --header=\"files:\"");
  FILE *fp = popen(run_command, "r");
  char selected[256];
  if (fgets(selected, sizeof(selected), fp) != NULL) 
  {
    // Run the selected test
    snprintf(run_command, sizeof(run_command), "./%s ../../tests/%s", app, selected);
    system(run_command);
  }
  pclose(fp);
  chdir("../..");
}

void clean() 
{
  printf(">>> Cleaning '%s' directory\n", build_dir);
  char clean_command[256];
  snprintf(clean_command, sizeof(clean_command), "rm -r %s", build_dir);
  system(clean_command);
}

int main() 
{
  app = "kaveh";
  mode = "debug";
  build_dir = "build/debug";

  char command[256];
  const char *commands[] = {"build", "debug", "run", "clean"};
  
  printf("Available commands:\n");
  for (int i = 0; i < sizeof(commands) / sizeof(commands[0]); i++) 
  {
    printf("%d: %s\n", i + 1, commands[i]);
  }

  printf("Select a command (1-%d): ", sizeof(commands) / sizeof(commands[0]));
  int choice;
  scanf("%d", &choice);

  if (choice < 1 || choice > sizeof(commands) / sizeof(commands[0])) 
  {
    printf("Invalid choice\n");
    return 1;
  }

  switch (choice) 
  {
    case 1:
      build();
      break;
    case 2:
      debug();
      break;
    case 3:
      run();
      break;
    case 4:
      clean();
      break;
    default:
      break;
  }
  return 0;
}
