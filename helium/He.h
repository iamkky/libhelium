#ifndef _HLIB_H_
#define _HLIB_H_

#include <stdarg.h>
#include <stdint.h>
#include <abd/StringBuffer.h>

typedef uint32_t hmagic;

#define HLIB_ELEMENT		0x454c454d
#define HLIB_ATTRIBUTE		0x41545452
#define HELIUM_TEXT_TAG		"_text"
#define HELIUM_LIST_TAG		"_list"

struct HNode_st;
typedef struct HNode_st *HNode;
typedef struct HNode_st HNode_st;

struct He_st;
typedef struct He_st *He;
typedef struct He_st He_st;

struct Hatt_st;
typedef struct HeAttr_st *HeAttr;
typedef struct HeAttr_st HeAttr_st;


struct HeAttr_st {
	hmagic	magic;
	char	*name;
	char	*value;
	void	*component;
	int	(*ptr)(void *component, char *value);
	HeAttr	next;
};

struct He_st {
	hmagic	magic;
	char	*face;
	char	*id;
	char	*cl;
	HeAttr	attribute;
	char	*content;
	He	child;
	He	child_last;
	He	next;
};

He	heNew(char *face, ...);
He	heNewv(char *face, va_list args);
void	heFree(He self);

void	heAddChild(He self, He child);
void	heAddChildv(He self, va_list args);
void	heAddAttribute(He self, HeAttr attr);


HeAttr	heAttrNew(char *name, char *value);
void	heAttrFree(HeAttr self);

// Utils
HeAttr	heClass(char *class_name);
HeAttr	heId(char *id_name);
He	heText(char *text);
He	heList();
He	heListv(va_list args);

// Renderers
void	heRender(He e, StringBuffer sb);

#endif
// EOF
