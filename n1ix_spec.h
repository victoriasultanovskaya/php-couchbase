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

#ifndef N1IX_SPEC_H_
#define N1IX_SPEC_H_

#include <php.h>
#include <libcouchbase/couchbase.h>
#include "bucket.h"

void couchbase_init_n1ix_spec(INIT_FUNC_ARGS);

int pcbc_make_n1ix_spec(zval *spec, zapval json TSRMLS_DC);

#endif // N1IX_SPEC_H_
