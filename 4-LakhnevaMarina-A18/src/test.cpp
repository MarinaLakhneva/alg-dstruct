#include "pch.h"
#include "lab_1.h"

TEST(TestForLab1, TestCreate) {
	char a[] = "dog";
	list* first_element = create(a);

	ASSERT_NE(nullptr, first_element);
	ASSERT_EQ(nullptr, first_element->next);
	ASSERT_EQ(first_element->value, a);
}

TEST(TestForLab1, TestCreate_nichego) {
	char a[] = { NULL };
	list* first_element = create(a);

	ASSERT_NE(nullptr, first_element);
	ASSERT_EQ(nullptr, first_element->next);
	ASSERT_EQ(first_element->value, a);
}

TEST(TestForLab1, TestAppendPysto) {
	struct list* pysto = (struct list*)malloc(sizeof(struct list*));
	pysto->value = NULL;
	pysto->next = NULL;


	char a[] = "information";
	list* new_element = append(a, NULL);

	ASSERT_NE(nullptr, a);
	ASSERT_EQ(NULL, new_element->next);
	ASSERT_EQ(new_element->value, a);
}

TEST(TestForLab1, TestAppend) {
	struct list* animal = (struct list*)malloc(sizeof(struct list*));
	list a = { "dog", NULL };
	list b = { "durk", &a };
	list c = { "donkey", &b };
	list d = { "monkey", &c	};
	list e = { "cat", &d };

	char f[] = "parrot";
	list* new_element = append(f, &e);

	ASSERT_NE(nullptr, f);
	ASSERT_EQ(&e,new_element->next);
	ASSERT_EQ(new_element->value, f);
}

TEST(TestForLab1, TestAppend1) {
	struct list* animal1 = (struct list*)malloc(sizeof(struct list*));
	list a = { "dog", NULL };
	list b = { "durk", &a };
	list c = { "donkey", &b };
	list d = { "monkey", &c };
	list e = { "cat", &d };

	char f[] = { NULL };
	list* new_element = append(f, NULL);

	ASSERT_NE(nullptr, f);
	ASSERT_NE(&e, new_element->next);
	ASSERT_EQ(new_element->value, f);
}

TEST(TestForLab1, TestSort) {
	struct list* animal2 = (struct list*)malloc(sizeof(struct list*));
	list a = { "dog", NULL };
	list b = { "durk", &a };
	list c = { "donkey", &b };
	list d = { "monkey", &c };
	list e = { "cat", &d };

	sort(&e);

	ASSERT_EQ(nullptr, &a);

	ASSERT_EQ(a, "cat");
	ASSERT_EQ(b, "dog");
	ASSERT_EQ(c, "donkey");
	ASSERT_EQ(d, "durk");
	ASSERT_EQ(e, "monkey");
}

TEST(TestForLab1, TestSort1) {
	struct list* animal3 = (struct list*)malloc(sizeof(struct list*));
	animal3->value = NULL;
	animal3->next = NULL;

	sort(animal3);

	ASSERT_EQ(nullptr, animal3);
}
