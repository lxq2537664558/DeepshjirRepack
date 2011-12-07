/*
 * Copyright (C) 2005-2011 MaNGOS <http://www.getmangos.com/>
 *
 * Copyright (C) 2008-2011 Trinity <http://www.trinitycore.org/>
 *
 * Copyright (C) 2010-2011 ArkCORE <http://www.arkania.net/>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 */

#include "ARC4.h"
#include <openssl/sha.h>

ARC4::ARC4(uint8 len)
{
    EVP_CIPHER_CTX_init(&m_ctx);
    EVP_EncryptInit_ex(&m_ctx, EVP_rc4(), NULL, NULL, NULL);
    EVP_CIPHER_CTX_set_key_length(&m_ctx, len);
}

ARC4::ARC4(uint8 *seed, uint8 len)
{
    EVP_CIPHER_CTX_init(&m_ctx);
    EVP_EncryptInit_ex(&m_ctx, EVP_rc4(), NULL, NULL, NULL);
    EVP_CIPHER_CTX_set_key_length(&m_ctx, len);
    EVP_EncryptInit_ex(&m_ctx, NULL, NULL, seed, NULL);
}

ARC4::~ARC4()
{
    EVP_CIPHER_CTX_cleanup(&m_ctx);
}

void ARC4::Init(uint8 *seed)
{
    EVP_EncryptInit_ex(&m_ctx, NULL, NULL, seed, NULL);
}

void ARC4::UpdateData(int len, uint8 *data)
{
    int outlen = 0;
    EVP_EncryptUpdate(&m_ctx, data, &outlen, data, len);
    EVP_EncryptFinal_ex(&m_ctx, data, &outlen);
}