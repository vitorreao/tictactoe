#include <stdlib.h>
#include <string.h>

#include <GDK_nodes.h>

#define GDK_NODE_LIST_INIT_CAP 5
#define GDK_NODE_LIST_EXPAND_MULTIPLE 2

struct p_GDK_node_list
{
	int capacity;
	int length;
	struct GDK_node **elements;
};

struct GDK_node
{
	char *name;
	GDK_update_func update;
	struct GDK_node *parent;
	struct p_GDK_node_list *children;
};

struct GDK_node *p_malloc_node(const char *name)
{
	if (name == NULL) name = "";
	size_t sizeof_name = sizeof(char) * (strlen(name) + 1); // +1 for \0
	struct GDK_node *node = malloc(sizeof(struct GDK_node) + sizeof_name);
	node->name = (char *)(node + sizeof(struct GDK_node));
	strcpy(node->name, name);
	return node;
}

struct p_GDK_node_list *p_malloc_children_list(int capacity)
{
	size_t struct_size = sizeof(struct p_GDK_node_list);
	size_t array_cap = sizeof(struct GDK_node *) * capacity;
	return (struct p_GDK_node_list *)malloc(struct_size + array_cap);
}

struct p_GDK_node_list *p_new_children_list()
{
	struct p_GDK_node_list *new_list =
		p_malloc_children_list(GDK_NODE_LIST_INIT_CAP);
	new_list->length = 0;
	new_list->capacity = GDK_NODE_LIST_INIT_CAP;
	new_list->elements = (struct GDK_node **)
		(new_list + sizeof(struct p_GDK_node_list));
	for (int i = 0; i < new_list->capacity; i++) {
		new_list->elements[i] = NULL;
	}
	return new_list;
}

struct p_GDK_node_list *p_expand_children_list(struct p_GDK_node_list *list)
{
	struct p_GDK_node_list *new_list =
		p_malloc_children_list(list->capacity * 2);
	new_list->length = list->length;
	new_list->capacity = list->capacity * 2;
	new_list->elements = (struct GDK_node **)
		(new_list + sizeof(struct p_GDK_node_list));
	for (int i = 0; i < list->capacity; i++) {
		new_list->elements[i] = list->elements[i];
	}
	for (int i = list->capacity; i < new_list->capacity; i++) {
		new_list->elements[i] = NULL;
	}
	return new_list;
}

struct GDK_node *GDK_new_node(const char *name, GDK_update_func update_func)
{
	struct GDK_node *new_node = p_malloc_node(name);
	new_node->update = update_func;
	new_node->parent = NULL;
	new_node->children = p_new_children_list();
	return new_node;
}

char *GDK_node_get_name(const struct GDK_node *node)
{
	return node->name;
}

GDK_update_func GDK_node_get_update_func(const struct GDK_node *node)
{
	return node->update;
}

struct GDK_node *GDK_node_get_parent(const struct GDK_node *node)
{
	return node->parent;
}

struct GDK_node *GDK_node_get_child_by_name(
	const struct GDK_node *parent,
	const char *name)
{
	for (int i = 0; i < parent->children->length; i++) {
		if (strcmp(parent->children->elements[i]->name, name) == 0) {
			return parent->children->elements[i];
		}
	}
	return NULL;
}

int GDK_node_get_children_len(const struct GDK_node *node)
{
	return node->children->length;
}

void GDK_attach_node(struct GDK_node *parent, struct GDK_node *child)
{
	if (parent->children->length == parent->children->capacity) {
		struct p_GDK_node_list *new_list =
			p_expand_children_list(parent->children);
		free(parent->children);
		parent->children = new_list;
		GDK_attach_node(parent, child);
		return;
	}
	parent->children->elements[parent->children->length] = child;
	parent->children->length++;
}

void GDK_free_node(struct GDK_node *node)
{
}
