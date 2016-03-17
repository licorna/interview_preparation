ll2:
	gcc linked_lib.c linked_list2.c -o ll2

ll1:
	gcc linked_lib.c linked_lists.c -o ll1

ll3:
	gcc linked_lib.c double_linked1.c -o ll3

all: ll1 ll2 ll3
