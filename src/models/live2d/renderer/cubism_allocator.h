// SPDX-License-Identifier: MIT
// SPDX-FileCopyrightText: 2023 MizunagiKB <mizukb@live.jp>

// SPDX-License-Identifier: MIT
// SPDX-FileCopyrightText: 2024 northernpaws

#ifndef VDOT_CUBISM_ALLOCATOR_H
#define VDOT_CUBISM_ALLOCATOR_H

#include <godot_cpp/core/memory.hpp>

#include <CubismFramework.hpp>
#include <ICubismAllocator.hpp>

class CubismAllocator : public Live2D::Cubism::Framework::ICubismAllocator {
  public:
    virtual void *Allocate( const Csm::csmSizeType size ) override {
        return memalloc( size );
    }

    virtual void Deallocate( void *addr ) override {
        if ( addr == nullptr ) {
            return;
        }
        memfree( addr );
    }

    virtual void *AllocateAligned( const Csm::csmSizeType size,
                                   const Csm::csmUint32 alignment ) override {
        size_t offset, shift, aligned_address;
        void *allocation, **preamble;

        offset = alignment - 1 + sizeof( void * );

        allocation = this->Allocate( size + static_cast<uint32_t>( offset ) );

        aligned_address = reinterpret_cast<size_t>( allocation ) + sizeof( void * );

        shift = aligned_address % alignment;

        if ( shift ) {
            aligned_address += ( alignment - shift );
        }

        preamble = reinterpret_cast<void **>( aligned_address );
        preamble[-1] = allocation;

        return reinterpret_cast<void *>( aligned_address );
    }

    virtual void DeallocateAligned( void *aligned_addr ) override {
        void **addr = reinterpret_cast<void **>( aligned_addr );
        this->Deallocate( addr[-1] );
    }
};

#endif // VDOT_CUBISM_ALLOCATOR_H
