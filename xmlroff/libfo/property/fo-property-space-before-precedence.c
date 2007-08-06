/* Fo
 * fo-property-space-before-precedence.c: 'space-before-precedence' property
 *
 * Copyright (C) 2001 Sun Microsystems
 * Copyright (C) 2007 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#include <string.h>
#include "fo-utils.h"
#include "fo-context.h"
#include "datatype/fo-datatype.h"
#include "property/fo-property-private.h"
#include "property/fo-property-font-size.h"
#include "property/fo-property-space-before-precedence.h"
#include "property/fo-property-util.h"

/* space-before-precedence */
/* Inherited: FALSE */
/* Shorthand: FALSE */
/* force | <integer> */
/* Initial value: space.minimum=0pt, .optimum=0pt, .maximum=0pt, .conditionality=discard, .precedence=0 */

struct _FoPropertySpaceBeforePrecedence
{
  FoProperty parent_instance;
};

struct _FoPropertySpaceBeforePrecedenceClass
{
  FoPropertyClass parent_class;
};

static void fo_property_space_before_precedence_init         (FoPropertySpaceBeforePrecedence      *property_space_before_precedence);
static void fo_property_space_before_precedence_class_init   (FoPropertySpaceBeforePrecedenceClass *klass);
static void fo_property_space_before_precedence_finalize     (GObject       *object);

static FoDatatype* fo_property_space_before_precedence_validate (FoDatatype *datatype,
                                                                 FoContext  *context,
                                                                 GError    **error);

static const gchar class_name[] = "FoPropertySpaceBeforePrecedence";
static gpointer parent_class;

/**
 * fo_property_space_before_precedence_get_type:
 * 
 * Register the #FoPropertySpaceBeforePrecedence type if not already registered and
 * return its #GType value.
 * 
 * Return value: #GType of #FoPropertySpaceBeforePrecedence.
 **/
GType
fo_property_space_before_precedence_get_type (void)
{
  static GType object_type = 0;

  if (!object_type)
    {
      static const GTypeInfo object_info =
      {
        sizeof (FoPropertySpaceBeforePrecedenceClass),
        NULL,           /* base_init */
        NULL,           /* base_finalize */
        (GClassInitFunc) fo_property_space_before_precedence_class_init,
        NULL,           /* class_finalize */
        NULL,           /* class_data */
        sizeof (FoPropertySpaceBeforePrecedence),
        0,              /* n_preallocs */
        (GInstanceInitFunc) fo_property_space_before_precedence_init,
	NULL		/* value_table */
      };

      object_type = g_type_register_static (FO_TYPE_PROPERTY,
                                            class_name,
                                            &object_info, 0);
    }

  return object_type;
}

/**
 * fo_property_space_before_precedence_init:
 * @space_before_precedence: #FoPropertySpaceBeforePrecedence object to initialise.
 * 
 * Implements #GInstanceInitFunc for #FoPropertySpaceBeforePrecedence.
 **/
void
fo_property_space_before_precedence_init (FoPropertySpaceBeforePrecedence *space_before_precedence)
{
  FO_PROPERTY (space_before_precedence)->value =
    g_object_ref (fo_integer_get_integer_zero ());
}

/**
 * fo_property_space_before_precedence_class_init:
 * @klass: #FoPropertySpaceBeforePrecedenceClass object to initialise.
 * 
 * Implements #GClassInitFunc for #FoPropertySpaceBeforePrecedenceClass.
 **/
void
fo_property_space_before_precedence_class_init (FoPropertySpaceBeforePrecedenceClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);
  FoPropertyClass *property_class = FO_PROPERTY_CLASS (klass);

  parent_class = g_type_class_peek_parent (klass);

  object_class->finalize = fo_property_space_before_precedence_finalize;

  property_class->is_inherited = FALSE;
  property_class->is_shorthand = FALSE;
  property_class->resolve_enum =
    fo_property_util_resolve_force_enum;
  property_class->validate =
    fo_property_space_before_precedence_validate;
  property_class->get_initial =
    fo_property_space_before_precedence_get_initial;
}

/**
 * fo_property_space_before_precedence_finalize:
 * @object: #FoPropertySpaceBeforePrecedence object to finalize.
 * 
 * Implements #GObjectFinalizeFunc for #FoPropertySpaceBeforePrecedence.
 **/
void
fo_property_space_before_precedence_finalize (GObject *object)
{
  FoPropertySpaceBeforePrecedence *space_before_precedence;

  space_before_precedence = FO_PROPERTY_SPACE_BEFORE_PRECEDENCE (object);

  G_OBJECT_CLASS (parent_class)->finalize (object);
}


/**
 * fo_property_space_before_precedence_new:
 * 
 * Creates a new #FoPropertySpaceBeforePrecedence initialized to default value.
 * 
 * Return value: the new #FoPropertySpaceBeforePrecedence.
 **/
FoProperty*
fo_property_space_before_precedence_new (void)
{
  FoProperty* space_before_precedence;

  space_before_precedence =
    FO_PROPERTY (g_object_new (fo_property_space_before_precedence_get_type (),
                               NULL));

  return space_before_precedence;
}

/**
 * fo_property_space_before_precedence_validate:
 * @datatype: #FoDatatype to be validated against allowed datatypes and
 *            values for current property.
 * @context:  #FoContext object from which to possibly inherit values.
 * @error:    Information about any error that has occurred.
 * 
 * Validates @datatype against allowed values.  Returns @datatype, a
 * replacement datatype value, or NULL if validation failed.
 * 
 * Return value: Valid datatype value or NULL.
 **/
FoDatatype*
fo_property_space_before_precedence_validate (FoDatatype *datatype,
                                              FoContext  *context,
                                              GError    **error)
{
  FoDatatype *new_datatype;

  g_return_val_if_fail (datatype != NULL, NULL);
  g_return_val_if_fail (FO_IS_DATATYPE (datatype), NULL);
  g_return_val_if_fail (context != NULL, NULL);
  g_return_val_if_fail (FO_IS_CONTEXT (context), NULL);
  g_return_val_if_fail (error == NULL || *error == NULL, NULL);

  if (FO_IS_ENUM (datatype))
    {
      return datatype;
    }
  else if (FO_IS_INTEGER (datatype))
    {
      return datatype;
    }
  else if (FO_IS_NUMBER (datatype))
    {
      new_datatype =
        fo_integer_new_with_value ((gint) fo_number_get_value (datatype));

      g_object_unref (datatype);

      return new_datatype;
    }
  else
    {
      gchar *datatype_sprintf = fo_object_sprintf (datatype);

      g_set_error (error,
		   FO_FO_ERROR,
		   FO_FO_ERROR_DATATYPE,
		   _(fo_fo_error_messages[FO_FO_ERROR_DATATYPE]),
		   class_name,
		   datatype_sprintf,
		   g_type_name (G_TYPE_FROM_INSTANCE (datatype)));

      g_object_unref (datatype);

      g_free (datatype_sprintf);

      return NULL;
    }
}

/**
 * fo_property_space_before_precedence_get_initial:
 * 
 * Get an instance of the property with the correct initial value.
 * 
 * Return value: An instance of the property.
 **/
FoProperty*
fo_property_space_before_precedence_get_initial (void)
{
  static FoProperty *space_before_precedence = NULL;

  if (space_before_precedence == NULL)
    {
      space_before_precedence =
	fo_property_space_before_precedence_new ();
    }

  return space_before_precedence;
}
