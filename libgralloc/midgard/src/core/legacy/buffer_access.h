/*
 * Copyright (C) 2018-2020 ARM Limited. All rights reserved.
 *
 * Copyright (C) 2008 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef BUFFER_ACCESS_H_
#define BUFFER_ACCESS_H_

namespace legacy
{

int mali_gralloc_lock(buffer_handle_t buffer, uint64_t usage, int l, int t, int w, int h,
                      void **vaddr);
int mali_gralloc_lock_ycbcr(buffer_handle_t buffer, uint64_t usage, int l, int t, int w,
                            int h, android_ycbcr *ycbcr);
int mali_gralloc_unlock(buffer_handle_t buffer);

int mali_gralloc_get_num_flex_planes(buffer_handle_t buffer, uint32_t *num_planes);
int mali_gralloc_lock_flex(buffer_handle_t buffer, uint64_t usage, int l, int t, int w, int h,
                           struct android_flex_layout *flex_layout);

}


#endif
