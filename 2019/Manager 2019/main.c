#include "user.h"
#include "menu.h"

int main(int argc, char* argv[]) {
  LOGIN* userlist[100]; // 사용자목록 포인터 배열 (최대 100)
  int is_login=0; // 로그인 여부 (0 NO, 1 Yes)
  int menu_id;
  char command[20];
  char echo[100];
  
  if (argc != 2) {
    printf("Usage : manager <datafile>\n");
    return 0;
  }
  int count = load_file(userlist, argv[1]);

  while(1){
    if(is_login==0){
      printf(">> ");
      scanf("%s", command);
      if(strcmp(command, "login")==0) is_login = login(userlist, count);
      else if(strcmp(command, "list")==0){
        printf("User list (id/password)\n");
        for(int i=0; i<count; i++){
          printf("%s %d\n", userlist[i]->id, userlist[i]->password); 
        }
      }
      else if(strcmp(command, "join")==0) {
        join(userlist, count);
        count = load_file(userlist, argv[1]);
        save_file(userlist, count, argv[1]);
      }
      else if(strcmp(command, "exit")==0) break;
      else printf("No such command!\n");
    }
    // 현재 로그인 되었는지의 여부를 파라미터로 알려야 한다.
    if(is_login == 1){
      while(strcmp(echo, "logout")==0){
        printf("#");
        scanf("%s", echo);
        printf("%s\n", echo);
        echo[0] = '\0';
      }
      printf("Bye!!\n");
    }
  }

  save_file(userlist, count, argv[1]);
  return 0;
}
