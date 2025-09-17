#include <stdio.h>
#include <malloc.h>
#include <ctype.h>
#include <stdlib.h>

typedef struct	node {
	enum {
		ADD,
		MULTI,
		VAL} type;
		int	val;
		struct node	*l;
		struct node *r;
} node;

node *new_node(node n)
{
	node	*ret = calloc(1, sizeof(node));
	if (!ret)
		return (NULL);
	*ret = n;
	return (ret);
}

void	destroy_tree(node *n)
{
	if (!n)
		return ;
	if (n->type != VAL)
	{
		destroy_tree(n->l);
		destroy_tree(n->r);
	}
	free(n);
}

void	unexpected(char c)
{
	if (c)
		printf("Unexpected token '%c'\n", c);
	else
		printf("Unexpected end of input\n");
}

int	accept (char **s, char c)
{
	if (**s == c)
	{
		(*s)++;
		return (1);
	}
	return (0);
}

// ...
static node	*parse_expr_rec(char **s);
static node	*parse_term(char **s);
static node	*parse_factor(char **s);


node	*parse_expr(char *
{
	// ...
    char *p = s;
    node *ret = parse_expr_rec(&p);
    if(!ret)
        return NULL;
	if (*p)
	{
        unexpected(*p);
		destroy_tree(ret);
		return (NULL);
	}
	return (ret);
}

static node	*parse_expr_rec(char **s)
{
    node *left = parse_term(s);
    if(!left)
        return NULL;
    while(accept(s, '+'))
    {
        node *right = parse_term(s);
        if(!right)
        {
            destroy_tree(left);
		    return (NULL);
        }
        node n = {
            .type = ADD,
            .val = 0,
            .l = left,
            .r = right
        };
        left = new_node(n);
    }
    return left;
}

static node	*parse_term(char **s)
{
    node *left = parse_factor(s);
    if(!left)
        return NULL;
    while(accept(s, '*'))
    {
        node *right = parse_factor(s);
        if(!right)
        {
            destroy_tree(left);
		    return (NULL);
        }
        node n = {
            .type = MULTI,
            .val = 0,
            .l = left,
            .r = right
        };
        left = new_node(n);
    }
    return left;
}

static node	*parse_factor(char **s)
{
    if(accept(s, '('))
    {
        node *sub = parse_expr_rec(s);
        if(!sub)
            return NULL;
        if(!accept(s, ')'))
        {
            if(**s)
                unexpected(**s);
            else
                unexpected(0);
            destroy_tree(sub);
            return NULL;
        }
        return sub;
    }
    if(isdigit((unsigned char)**s))
    {
        node n = {
            .type = VAL,
            .val = **s - '0',
            .l = NULL,
            .r = NULL
        };
        (*s)++;
        return(new_node(n));
    }
    if(**s)
        unexpected(**s);
    else
        unexpected(0);
    return NULL;
}


int	eval_tree(node *tree)
{
	switch (tree->type)
	{
		case ADD:
			return (eval_tree(tree->l) + eval_tree(tree->r));
		case MULTI:
			return (eval_tree(tree->l) * eval_tree(tree->r));
		case VAL:
			return (tree->val);
	}
}

int	main(int ac, char **av)
{
	if (ac != 2)
		return (1);
	node *tree = parse_expr(av[1]);
	if (!tree)
		return (1);
	printf("%d\n", eval_tree(tree));
	destroy_tree(tree);
	return (0);
}
