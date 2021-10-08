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
	char a[] = {NULL};
	list* first_element = create(a);

	ASSERT_NE(nullptr, first_element);
	ASSERT_EQ(nullptr, first_element->next);
	ASSERT_STREQ(first_element->value, a);
}

TEST(TestForLab1, TestAppendPysto) {
	struct list* nothing = (struct list*)malloc(sizeof(struct list));
	nothing->value = NULL;
	nothing->next = NULL;


	char a[] = "information";
	list* new_element = append(a, NULL);

	ASSERT_NE(nullptr, a);
	ASSERT_EQ(NULL, new_element->next);
	ASSERT_STREQ(new_element->value, a);
}

TEST(TestForLab1, TestAppend) {
	list* a = (list*)malloc(sizeof(list));
	a->value = ("dog");
	a->next = NULL;

	list* b = (list*)malloc(sizeof(list));
	b->value = ("durk");
	b->next = a;

	list* c = (list*)malloc(sizeof(list));
	c->value = ("donkey");
	c->next = b;

	list* d = (list*)malloc(sizeof(list));
	d->value = ("monkey");
	d->next = c;

	list* e = (list*)malloc(sizeof(list));
	e->value = "cat";
	e->next = d;

	char f[] = "parrot";
	list* new_element = append(f, e);

	ASSERT_NE(nullptr, f);
	ASSERT_EQ(e, new_element->next);
	ASSERT_STREQ(new_element->value, f);
}

TEST(TestForLab1, TestAppend1) {
	list* a = (list*)malloc(sizeof(list));
	a->value = ("dog");
	a->next = NULL;

	list* b = (list*)malloc(sizeof(list));
	b->value = ("durk");
	b->next = a;

	list* c = (list*)malloc(sizeof(list));
	c->value = ("donkey");
	c->next = b;

	list* d = (list*)malloc(sizeof(list));
	d->value = ("monkey");
	d->next = c;

	list* e = (list*)malloc(sizeof(list));
	e->value = ("cat");
	e->next = d;

	char f[] = { NULL };
	list* new_element = append(f, NULL);

	ASSERT_NE(nullptr, f);
	ASSERT_NE(e, new_element->next);
	ASSERT_STREQ(new_element->value, f);
}

TEST(TestForLab1, TestSort) {
	list* a = (list*)malloc(sizeof(list));
	a->value = "dog";
	a->next = NULL;

	list* b = (list*)malloc(sizeof(list));
	b->value = "durk";
	b->next = a;

	list* c = (list*)malloc(sizeof(list));
	c->value = "donkey";
	c->next = b;

	list* d = (list*)malloc(sizeof(list));
	d->value = "monkey";
	d->next = c;

	list* e = (list*)malloc(sizeof(list));
	e->value = "cat";
	e->next = d;

	sort(e);

	ASSERT_EQ(nullptr, a->next);
	
	ASSERT_STREQ(a->value, "monkey");
	ASSERT_STREQ(b->value, "durk");
	ASSERT_STREQ(c->value, "donkey");
	ASSERT_STREQ(d->value, "dog");
	ASSERT_STREQ(e->value, "cat");

}

TEST(TestForLab1, TestSort1) {
	list* a = (list*)malloc(sizeof(list));
	a->value = "monkey";
	a->next = NULL;

	list* b = (list*)malloc(sizeof(list));
	b->value = "durk";
	b->next = a;

	list* c = (list*)malloc(sizeof(list));
	c->value = "donkey";
	c->next = b;

	list* d = (list*)malloc(sizeof(list));
	d->value = "dog";
	d->next = c;

	list* e = (list*)malloc(sizeof(list));
	e->value = "cat";
	e->next = d;

	sort(e);

	ASSERT_EQ(nullptr, a->next);

	ASSERT_STREQ(a->value, "monkey");
	ASSERT_STREQ(b->value, "durk");
	ASSERT_STREQ(c->value, "donkey");
	ASSERT_STREQ(d->value, "dog");
	ASSERT_STREQ(e->value, "cat");

}

TEST(TestForLab1, TestSort2) {
	struct list* animal3 = (struct list*)malloc(sizeof(struct list));
	animal3->value = NULL;
	animal3->next = NULL;

	sort(animal3);

	ASSERT_EQ(nullptr, animal3->value);
}