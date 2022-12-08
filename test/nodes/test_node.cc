#include <gtest/gtest.h>

extern "C" {
	#include <GDK_nodes.h>
}

namespace
{
	TEST(GDK_node, NewNodeWithNullUpdate)
	{
		struct GDK_node *new_node = GDK_new_node("world", NULL);
		std::string actual_name(GDK_node_get_name(new_node));
		std::string expected_name("world");
		EXPECT_EQ(expected_name, actual_name);
		EXPECT_EQ(NULL, GDK_node_get_parent(new_node));
		EXPECT_EQ(NULL, GDK_node_get_update_func(new_node));
		EXPECT_EQ(0, GDK_node_get_children_len(new_node));
	}

	TEST(GDK_node, AttachNodeBeyondCapacity)
	{
		struct GDK_node *parent = GDK_new_node("parent", NULL);

		struct GDK_node *child = GDK_new_node("child1", NULL);
		GDK_attach_node(parent, child);

		child = GDK_new_node("child2", NULL);
		GDK_attach_node(parent, child);

		child = GDK_new_node("child3", NULL);
		GDK_attach_node(parent, child);

		child = GDK_new_node("child4", NULL);
		GDK_attach_node(parent, child);

		child = GDK_new_node("child5", NULL);
		GDK_attach_node(parent, child);

		child = GDK_new_node("child6", NULL);
		GDK_attach_node(parent, child);

		EXPECT_EQ(6, GDK_node_get_children_len(parent));

		child = GDK_node_get_child_by_name(parent, "child1");
		EXPECT_STREQ("child1", GDK_node_get_name(child));

		child = GDK_node_get_child_by_name(parent, "child2");
		EXPECT_STREQ("child2", GDK_node_get_name(child));

		child = GDK_node_get_child_by_name(parent, "child3");
		EXPECT_STREQ("child3", GDK_node_get_name(child));

		child = GDK_node_get_child_by_name(parent, "child4");
		EXPECT_STREQ("child4", GDK_node_get_name(child));

		child = GDK_node_get_child_by_name(parent, "child5");
		EXPECT_STREQ("child5", GDK_node_get_name(child));

		child = GDK_node_get_child_by_name(parent, "child6");
		EXPECT_STREQ("child6", GDK_node_get_name(child));
	}
}
