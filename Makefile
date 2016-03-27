ll2:
	gcc linked_lib.c linked_list2.c -o ll2

ll1:
	gcc linked_lib.c linked_lists.c -o ll1

ll3:
	gcc linked_lib.c double_linked1.c -o ll3

ll4:
	gcc chapter4_2.c -o ll4

ll5:
	gcc chapter5_1.c -o ll4

all:
	ll1 ll2 ll3 ll4 ll5
