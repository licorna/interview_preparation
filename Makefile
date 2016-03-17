ll2:
	gcc linked_lib.c linked_list2.c -o ll2

ll1:
	gcc linked_lib.c linked_lists.c -o ll1

all: ll1 ll2
