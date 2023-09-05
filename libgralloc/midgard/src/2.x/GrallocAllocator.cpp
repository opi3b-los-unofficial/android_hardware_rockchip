/*
 * Copyright (C) 2017-2020 ARM Limited. All rights reserved.
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

#include "GrallocAllocator.h"
#include "hidl_common/BufferDescriptor.h"
#include "hidl_common/Allocator.h"
#include "allocator/mali_gralloc_ion.h"
#include "fbdev/mali_gralloc_framebuffer.h"

namespace arm
{
namespace allocator
{

using android::hardware::graphics::allocator::V2_0::IAllocator;
using android::hardware::graphics::mapper::V2_0::Error;
using android::hardware::Return;
using android::hardware::hidl_handle;
using android::hardware::hidl_vec;
using android::hardware::Void;
using android::hardware::hidl_string;

GrallocAllocator::GrallocAllocator()
{
}

GrallocAllocator::~GrallocAllocator()
{
	mali_gralloc_ion_close();
}

Return<void> GrallocAllocator::dumpDebugInfo(dumpDebugInfo_cb hidl_cb)
{
	hidl_cb(hidl_string());
	return Void();
}

Return<void> GrallocAllocator::allocate(const BufferDescriptor &descriptor, uint32_t count, allocate_cb hidl_cb)
{
	buffer_descriptor_t bufferDescriptor;
	if (!mapper::common::grallocDecodeBufferDescriptor(descriptor, bufferDescriptor))
	{
		hidl_cb(Error::BAD_DESCRIPTOR, 0, hidl_vec<hidl_handle>());
		return Void();
	}
	common::allocate(bufferDescriptor, count, hidl_cb,
	                 [this](const buffer_descriptor_t *descriptor, buffer_handle_t *handle) -> int
	                 {
		                 return mali_gralloc_fb_allocate(&private_module, descriptor, handle);
		             });
	return Void();
}

} // namespace allocator
} // namespace arm

extern "C" IAllocator *HIDL_FETCH_IAllocator(const char * /* name */)
{
	MALI_GRALLOC_LOGV("Arm Module IAllocator %d.%d, pid = %d ppid = %d", GRALLOC_VERSION_MAJOR,
	                  (HIDL_ALLOCATOR_VERSION_SCALED - (GRALLOC_VERSION_MAJOR * 100)) / 10, getpid(), getppid());

	return new arm::allocator::GrallocAllocator();
}