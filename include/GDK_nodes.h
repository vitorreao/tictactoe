#ifndef GDK_NODES_H
#define GDK_NODES_H

typedef void (*GDK_update_func)();

struct GDK_node;

struct GDK_node *GDK_new_node(const char *name, GDK_update_func update);

char *GDK_node_get_name(const struct GDK_node *node);

GDK_update_func GDK_node_get_update_func(const struct GDK_node *node);

struct GDK_node *GDK_node_get_parent(const struct GDK_node *node);

int GDK_node_get_children_len(const struct GDK_node *node);

struct GDK_node *GDK_node_get_child_by_name(
	const struct GDK_node *parent,
	const char *name);

void GDK_attach_node(struct GDK_node *parent, struct GDK_node *child);

void GDK_free_node(struct GDK_node *node);

#endif /* GDK_NODES_H */
