#include "pch.h"
#include "Labaratornay/LaBa.h"


TEST(TestForLab1, TestCreate) {
	char a[] = "dog";
	list* first_element = create(a);

	ASSERT_NE(nullptr, first_element);
	ASSERT_EQ(nullptr, first_element->next);
	ASSERT_STREQ(first_element->value, a);
}

TEST(TestForLab1, TestCreate_nichego) {
	char a[] = { NULL };
	list* first_element = create(a);

	ASSERT_NE(nullptr, first_element);
	ASSERT_EQ(nullptr, first_element->next);
	ASSERT_STREQ(first_element->value, a);
}

TEST(TestForLab1, TestAppendPysto) {
	struct list* nothing = (struct list*)malloc(sizeof(struct list));
	nothing->value = NULL;
	nothing->next = NULL;
	if (nothing == NULL) {
		printf("No memory allocated!");
		return;
	}

	char a[] = "information";
	list* new_element = append(a, NULL);

	ASSERT_NE(nullptr, a);
	ASSERT_EQ(NULL, new_element->next);
	ASSERT_STREQ(new_element->value, a);
}

TEST(TestForLab1, TestAppend) {

	list list_5 = { "1", NULL };
	list list_4 = { "8", &list_5 };
	list list_3 = { "7", &list_4 };
	list list_2 = { "5", &list_3 };
	list list_1 = { "3", &list_2 };

	char list_6[] = "6";
	list* new_element = append(list_6, &list_1);

	ASSERT_NE(nullptr, list_6);
	ASSERT_EQ(&list_1, new_element->next);
	ASSERT_STREQ(new_element->value, list_6);
}

TEST(TestForLab1, TestAppend1) {

	list list_5 = { "1", NULL };
	list list_4 = { "8", &list_5 };
	list list_3 = { "7", &list_4 };
	list list_2 = { "5", &list_3 };
	list list_1 = { "3", &list_2 };

	char list_6[] = { NULL };
	list* new_element = append(list_6, NULL);

	ASSERT_NE(nullptr, list_6);
	ASSERT_NE(&list_1, new_element->next);
	ASSERT_STREQ(new_element->value, list_6);
}

TEST(TestForLab1, TestSort) {

	list list_5 = { "5", NULL };
	list list_4 = { "4", &list_5 };
	list list_3 = { "3", &list_4 };
	list list_2 = { "2", &list_3 };
	list list_1 = { "1", &list_2 };
	sort(&list_1);

	ASSERT_EQ(nullptr, list_5.next);

	ASSERT_STREQ(list_1.value, "1");
	ASSERT_STREQ(list_2.value, "2");
	ASSERT_STREQ(list_3.value, "3");
	ASSERT_STREQ(list_4.value, "4");
	ASSERT_STREQ(list_5.value, "5");

}

TEST(TestForLab1, TestSort1) {

	list list_5 = { "1", NULL };
	list list_4 = { "2", &list_5 };
	list list_3 = { "3", &list_4 };
	list list_2 = { "4", &list_3 };
	list list_1 = { "5", &list_2 };
	sort(&list_1);

	ASSERT_EQ(nullptr, list_5.next);

	ASSERT_STREQ(list_1.value, "1");
	ASSERT_STREQ(list_2.value, "2");
	ASSERT_STREQ(list_3.value, "3");
	ASSERT_STREQ(list_4.value, "4");
	ASSERT_STREQ(list_5.value, "5");

}

TEST(TestForLab1, TestSort2) {

	list list_5 = { "1", NULL };
	list list_4 = { "8", &list_5 };
	list list_3 = { "7", &list_4 };
	list list_2 = { "5", &list_3 };
	list list_1 = { "3", &list_2 };
	sort(&list_1);

	ASSERT_EQ(nullptr, list_5.next);

	ASSERT_STREQ(list_1.value, "1");
	ASSERT_STREQ(list_2.value, "3");
	ASSERT_STREQ(list_3.value, "5");
	ASSERT_STREQ(list_4.value, "7");
	ASSERT_STREQ(list_5.value, "8");

}
