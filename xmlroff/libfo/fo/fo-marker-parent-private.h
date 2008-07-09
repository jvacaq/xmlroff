/* Fo
 * fo-marker-parent-private.h: Formatting object that is parent of possible fo:marker
 *
 * Copyright (C) 2001 Sun Microsystems
 * Copyright (C) 2007-2008 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#include <libfo/fo/fo-idable-private.h>
#include <libfo/fo/fo-marker-parent.h>

struct _FoMarkerParent
{
  FoIdable parent_instance;

  GList *marker_list;
};

struct _FoMarkerParentClass
{
  FoIdableClass parent_class;
};
