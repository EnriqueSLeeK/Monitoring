#ifndef STRUCTURE
# define STRUCTURE

typedef struct	base_fields
{
	char	*protocol;
	char	*name;
	char	*addr;
	void	(*show)(void *self, void *info);
	void	(*write)(void *self, void *info);
	void	(*destroy)(void *self);
	void	*(*monitor)(void *self);
} t_base;

void	init_base(t_base *self, char *name,
		char *protocol, char *addr,
		void (*show)(void *self, void *info),
		void (*write)(void *self, void *info),
		void (*destroy)(void *self),
		void *(*monitor)(void *self));

void	destroy_base(t_base *self);

#endif
