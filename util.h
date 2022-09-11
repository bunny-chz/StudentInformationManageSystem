#ifndef __UTIL_H__
#define __UTIL_H__

//打印十.八.十六进制
#define PRI_D(a) printf(#a" : %d\n", a)
#define PRI_O(a) printf(#a" : %#o\n", a)
#define PRI_H(a) printf(#a" : %#x\n", a)

#define PRI_S(a) printf(#a" : %s\n", a)

#define GETFGETS(string, s)					\
			do {							\
				printf(string);					\
				fgets(s, sizeof(s), stdin);		\
				if(s[strlen(s) - 1] == '\n')	\
					s[strlen(s) - 1] = '\0';	\
			}while(0)	


#define ERRP(con, str, ret) do{						\
				if (con)							\
				{									\
					printf("%s false!\n", str);		\
					ret;							\
				}									\
			}while(0)

#endif //UTIL_H
