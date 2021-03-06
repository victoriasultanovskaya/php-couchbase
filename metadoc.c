/**
 *     Copyright 2016 Couchbase, Inc.
 *
 *   Licensed under the Apache License, Version 2.0 (the "License");
 *   you may not use this file except in compliance with the License.
 *   You may obtain a copy of the License at
 *
 *       http://www.apache.org/licenses/LICENSE-2.0
 *
 *   Unless required by applicable law or agreed to in writing, software
 *   distributed under the License is distributed on an "AS IS" BASIS,
 *   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *   See the License for the specific language governing permissions and
 *   limitations under the License.
 */

#include "bucket.h"
#include "cas.h"
#include "transcoding.h"
#include "exception.h"

zend_class_entry *metadoc_ce;

zend_function_entry metadoc_methods[] = {
    { NULL, NULL, NULL }
};

void couchbase_init_metadoc(INIT_FUNC_ARGS)
{
    zend_class_entry ce;

    INIT_CLASS_ENTRY(ce, "CouchbaseMetaDoc", metadoc_methods);
    metadoc_ce = zend_register_internal_class(&ce TSRMLS_CC);

    zend_declare_property_null(metadoc_ce, "error", strlen("error"), ZEND_ACC_PUBLIC TSRMLS_CC);
    zend_declare_property_null(metadoc_ce, "value", strlen("value"), ZEND_ACC_PUBLIC TSRMLS_CC);
    zend_declare_property_null(metadoc_ce, "flags", strlen("flags"), ZEND_ACC_PUBLIC TSRMLS_CC);
    zend_declare_property_null(metadoc_ce, "cas", strlen("cas"), ZEND_ACC_PUBLIC TSRMLS_CC);
    zend_declare_property_null(metadoc_ce, "token", strlen("token"), ZEND_ACC_PUBLIC TSRMLS_CC);
}

int make_metadoc_error(zval *doc, lcb_error_t err TSRMLS_DC)
{
    zapval zerror;

    object_init_ex(doc, metadoc_ce);
    make_lcb_exception(&zerror, err, NULL TSRMLS_CC);
    zend_update_property(metadoc_ce, doc, "error", sizeof("error") - 1,
        zapval_zvalptr(zerror) TSRMLS_CC);

    zapval_destroy(zerror);
    return SUCCESS;
}

int make_metadoc(zval *doc, zapval *value, zapval *flags, zapval *cas, zapval *token TSRMLS_DC)
{
   object_init_ex(doc, metadoc_ce);

   if (value) {
       zend_update_property(metadoc_ce, doc, "value", sizeof("value") - 1, zapval_zvalptr_p(value) TSRMLS_CC);
   }
   if (flags) {
       zend_update_property(metadoc_ce, doc, "flags", sizeof("flags") - 1, zapval_zvalptr_p(flags) TSRMLS_CC);
   }
   if (cas) {
       zend_update_property(metadoc_ce, doc, "cas", sizeof("cas") - 1, zapval_zvalptr_p(cas) TSRMLS_CC);
   }
   if (token && zapval_zvalptr_p(token) && !zap_zval_is_null(zapval_zvalptr_p(token))) {
       zend_update_property(metadoc_ce, doc, "token", sizeof("token") - 1, zapval_zvalptr_p(token) TSRMLS_CC);
   }

   return SUCCESS;
}
