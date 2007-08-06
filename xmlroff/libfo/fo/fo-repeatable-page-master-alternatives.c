/* Fo
 * fo-repeatable-page-master-alternatives.c: 'repeatable-page-master-alternatives' formatting object
 *
 * Copyright (C) 2001-2005 Sun Microsystems
 * Copyright (C) 2007 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#include "fo/fo-repeatable-page-master-alternatives-private.h"
#include "fo/fo-conditional-page-master-reference.h"

static void fo_repeatable_page_master_alternatives_class_init  (FoRepeatablePageMasterAlternativesClass *klass);
static void fo_repeatable_page_master_alternatives_finalize    (GObject           *object);
static gboolean fo_repeatable_page_master_alternatives_validate_content (FoFo    *fo,
                                                                         GError **error);
static void fo_repeatable_page_master_alternatives_validate (FoFo      *fo,
                                                             FoContext *current_context,
                                                             FoContext *parent_context,
                                                             GError   **error);
static void fo_repeatable_page_master_alternatives_update_from_context (FoFo      *fo,
                                                                        FoContext *context);
static void fo_repeatable_page_master_alternatives_debug_dump_properties (FoFo *fo,
                                                                          gint  depth);

static gpointer parent_class;

/**
 * fo_repeatable_page_master_alternatives_get_type:
 * 
 * Register the #FoRepeatablePageMasterAlternatives object type.
 * 
 * Return value: #GType value of the #FoRepeatablePageMasterAlternatives object type.
 **/
GType
fo_repeatable_page_master_alternatives_get_type (void)
{
  static GType object_type = 0;

  if (!object_type)
    {
      static const GTypeInfo object_info =
      {
        sizeof (FoRepeatablePageMasterAlternativesClass),
        NULL,           /* base_init */
        NULL,           /* base_finalize */
        (GClassInitFunc) fo_repeatable_page_master_alternatives_class_init,
        NULL,           /* class_finalize */
        NULL,           /* class_data */
        sizeof (FoRepeatablePageMasterAlternatives),
        0,              /* n_preallocs */
        NULL,		/* instance_init */
	NULL		/* value_table */
      };

      object_type = g_type_register_static (FO_TYPE_FO,
                                            "FoRepeatablePageMasterAlternatives",
                                            &object_info, 0);
    }

  return object_type;
}

/**
 * fo_repeatable_page_master_alternatives_class_init:
 * @klass: #FoRepeatablePageMasterAlternativesClass object to initialise.
 * 
 * Implements #GClassInitFunc for #FoRepeatablePageMasterAlternativesClass.
 **/
void
fo_repeatable_page_master_alternatives_class_init (FoRepeatablePageMasterAlternativesClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);
  FoFoClass *fofo_class = FO_FO_CLASS (klass);

  parent_class = g_type_class_peek_parent (klass);

  object_class->finalize = fo_repeatable_page_master_alternatives_finalize;

  fofo_class->validate_content = fo_repeatable_page_master_alternatives_validate_content;
  fofo_class->validate2 = fo_repeatable_page_master_alternatives_validate;
  fofo_class->update_from_context = fo_repeatable_page_master_alternatives_update_from_context;
  fofo_class->debug_dump_properties = fo_repeatable_page_master_alternatives_debug_dump_properties;
}

/**
 * fo_repeatable_page_master_alternatives_finalize:
 * @object: #FoRepeatablePageMasterAlternatives object to finalize.
 * 
 * Implements #GObjectFinalizeFunc for #FoRepeatablePageMasterAlternatives.
 **/
void
fo_repeatable_page_master_alternatives_finalize (GObject *object)
{
  FoRepeatablePageMasterAlternatives *fo_repeatable_page_master_alternatives;

  fo_repeatable_page_master_alternatives = FO_REPEATABLE_PAGE_MASTER_ALTERNATIVES (object);

  G_OBJECT_CLASS (parent_class)->finalize (object);
}

/**
 * fo_repeatable_page_master_alternatives_new:
 * 
 * Creates a new #FoRepeatablePageMasterAlternatives initialized to default value.
 * 
 * Return value: the new #FoRepeatablePageMasterAlternatives.
 **/
FoFo*
fo_repeatable_page_master_alternatives_new (void)
{
  return FO_FO (g_object_new (fo_repeatable_page_master_alternatives_get_type (),
                              NULL));
}

/**
 * fo_repeatable_page_master_alternatives_validate_content:
 * @fo:    #FoRepeatablePageMasterAlternatives object to validate.
 * @error: #GError indicating error condition, if any.
 * 
 * Validate the content model, i.e., the structure, of the object.
 * Return value matches #GNodeTraverseFunc model: %FALSE indicates
 * content model is correct, or %TRUE indicates an error.  When used
 * with fo_node_traverse(), returning %TRUE stops the traversal.
 * 
 * Return value: %FALSE if content model okay, %TRUE if not.
 **/
gboolean
fo_repeatable_page_master_alternatives_validate_content (FoFo    *fo,
                                                         GError **error)
{
  GError *tmp_error = NULL;

  g_return_val_if_fail (fo != NULL, TRUE);
  g_return_val_if_fail (FO_IS_REPEATABLE_PAGE_MASTER_ALTERNATIVES (fo), TRUE);
  g_return_val_if_fail (error == NULL || *error == NULL, TRUE);

  FoNode *child_node = fo_node_first_child (FO_NODE (fo));

  while (child_node)
    {
      if (FO_IS_CONDITIONAL_PAGE_MASTER_REFERENCE (child_node))
 	{
 	  child_node = fo_node_next_sibling (child_node);
 	}
      else
 	{
 	  tmp_error = g_error_new (FO_FO_ERROR,
 				   FO_FO_ERROR_INVALID_CONTENT,
 				   _(fo_fo_error_messages[FO_FO_ERROR_INVALID_CONTENT]),
 				   fo_object_sprintf (FO_OBJECT (fo)));
 
 	  return fo_object_log_or_propagate_error (FO_OBJECT (fo),
 						   error,
 						   tmp_error);
 	}
    }
  return FALSE;

  /*
    error:
    tmp_error = g_error_new (FO_FO_ERROR,
    FO_FO_ERROR_INVALID_CONTENT,
    _(fo_fo_error_messages[FO_FO_ERROR_INVALID_CONTENT]),
    fo_object_sprintf (fo));

    return fo_object_log_or_propagate_error (FO_OBJECT (fo),
    error,
    tmp_error);
  */
}

/**
 * fo_repeatable_page_master_alternatives_validate:
 * @fo:              #FoRepeatablePageMasterAlternatives object to validate.
 * @current_context: #FoContext associated with current object.
 * @parent_context:  #FoContext associated with parent FO.
 * @error:           Information about any error that has occurred.
 * 
 * Validate and possibly update interrelated property values in
 * @current_context, then update @fo property values.  Set @error if
 * an error occurred.
 **/
void
fo_repeatable_page_master_alternatives_validate (FoFo      *fo,
                                                 FoContext *current_context,
                                                 FoContext *parent_context,
                                                 GError   **error)
{
  FoRepeatablePageMasterAlternatives *fo_repeatable_page_master_alternatives;

  g_return_if_fail (fo != NULL);
  g_return_if_fail (FO_IS_REPEATABLE_PAGE_MASTER_ALTERNATIVES (fo));
  g_return_if_fail (FO_IS_CONTEXT (current_context));
  g_return_if_fail (FO_IS_CONTEXT (parent_context));
  g_return_if_fail (error == NULL || *error == NULL);

  fo_repeatable_page_master_alternatives = FO_REPEATABLE_PAGE_MASTER_ALTERNATIVES (fo);

  fo_context_merge (current_context, parent_context);
  fo_fo_update_from_context (fo, current_context);
}

/**
 * fo_repeatable_page_master_alternatives_update_from_context:
 * @fo:      The #FoFo object.
 * @context: The #FoContext object from which to update the properties of @fo.
 * 
 * Sets the properties of @fo to the corresponding property values in @context.
 **/
void
fo_repeatable_page_master_alternatives_update_from_context (FoFo      *fo,
                                                            FoContext *context)
{
  g_return_if_fail (fo != NULL);
  g_return_if_fail (FO_IS_REPEATABLE_PAGE_MASTER_ALTERNATIVES (fo));
  g_return_if_fail (context != NULL);
  g_return_if_fail (FO_IS_CONTEXT (context));

}

/**
 * fo_repeatable_page_master_alternatives_debug_dump_properties:
 * @fo:    The #FoFo object.
 * @depth: Indent level to add to the output.
 * 
 * Calls #fo_object_debug_dump on each property of @fo then calls
 * debug_dump_properties method of parent class.
 **/
void
fo_repeatable_page_master_alternatives_debug_dump_properties (FoFo *fo,
                                                              gint  depth)
{
  FoRepeatablePageMasterAlternatives *fo_repeatable_page_master_alternatives;

  g_return_if_fail (fo != NULL);
  g_return_if_fail (FO_IS_REPEATABLE_PAGE_MASTER_ALTERNATIVES (fo));

  fo_repeatable_page_master_alternatives = FO_REPEATABLE_PAGE_MASTER_ALTERNATIVES (fo);

  g_log (G_LOG_DOMAIN,
	 G_LOG_LEVEL_DEBUG,
         "(No properties)");

  FO_FO_CLASS (parent_class)->debug_dump_properties (fo, depth + 1);
}
