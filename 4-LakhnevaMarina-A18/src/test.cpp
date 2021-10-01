#include "pch.h"
#include "lab_1.h"


TEST(TestForLab1, TestCreate) {
	char a1[] = "dog";
	list* first_element = create(a1);

	ASSERT_NE(nullptr, first_element);
	ASSERT_EQ(nullptr, first_element -> next);
	ASSERT_EQ(first_element -> value, a1);
}

TEST(TestForLab1, TestAppend) {
	char a1[] = "dog";
	list* first_element = create (a1);

	char a2[] = "cat";
	list* second_element = append (a2, first_element);

	ASSERT_NE(nullptr, second_element);
	ASSERT_EQ(second_element -> next, first_element);
	ASSERT_EQ(second_element -> value, "cat");
}

TEST(TestForLab1, TestSort) {
	char a1[] = "dog";
	list* first_element = create(a1);

	char a2[] = "cat";
	list* second_element = append(a2, first_element);

	char a3[] = "lamb";
	list* third_element = append(a3, second_element);

	sort(third_element);

	ASSERT_EQ(nullptr, first_element->next);

	ASSERT_EQ(first_element->value, "cat");
	ASSERT_EQ(second_element->value, "dog");
	ASSERT_EQ(third_element->value, "lamb");
}