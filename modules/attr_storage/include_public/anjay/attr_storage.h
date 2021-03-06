/*
 * Copyright 2017 AVSystem <avsystem@avsystem.com>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef ANJAY_INCLUDE_ANJAY_ATTR_STORAGE_H
#define ANJAY_INCLUDE_ANJAY_ATTR_STORAGE_H

#include <avsystem/commons/stream.h>

#include <anjay/anjay.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Installs the Attribute Storage handlers in an Anjay object, making it
 * possible to automatically manage attributes for LwM2M Objects, their
 * instances and resources.
 *
 * In accordance to the LwM2M specification, there are three levels on which
 * attributes may be stored:
 *
 * - Resource level (@ref anjay_dm_resource_read_attrs_t,
 *   @ref anjay_dm_resource_write_attrs_t)
 * - Instance level (@ref anjay_dm_instance_read_default_attrs_t,
 *   @ref anjay_dm_instance_write_default_attrs_t)
 * - Object level (@ref anjay_dm_object_read_default_attrs_t,
 *   @ref anjay_dm_object_write_default_attrs_t)
 *
 * If at least one of either read or write handlers is provided in a given
 * object for a given level, attribute handling on that level will not be
 * altered, but instead any calls will be directly forwarded to the original
 * handlers.
 *
 * If both read and write handlers are left as NULL in a given object for a
 * given level, attribute storage will be handled by the Attribute Storage
 * module instead, implementing both handlers.
 *
 * The Attribute Storage module does not require explicit cleanup; all resources
 * will be automatically freed up during the call to @ref anjay_delete.
 *
 * @param anjay ANJAY object for which the Attribute Storage is installed.
 *
 * @returns 0 on success, or a negative value in case of error.
 */
int anjay_attr_storage_install(anjay_t *anjay);

/**
 * Checks whether the attribute storage has been modified since last call to
 * @ref anjay_attr_storage_persist or @ref anjay_attr_storage_restore.
 */
bool anjay_attr_storage_is_modified(anjay_t *anjay);

int anjay_attr_storage_persist(anjay_t *anjay,
                               avs_stream_abstract_t *out_stream);

int anjay_attr_storage_restore(anjay_t *anjay,
                               avs_stream_abstract_t *in_stream);

#ifdef __cplusplus
}
#endif

#endif /* ANJAY_INCLUDE_ANJAY_ATTR_STORAGE_H */
