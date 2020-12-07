//  ────────────────────────────────────────────────────────────
//                     ╔╗  ╔╗ ╔══╗      ╔════╗
//                     ║╚╗╔╝║ ╚╣╠╝      ║╔╗╔╗║
//                     ╚╗╚╝╔╝  ║║  ╔══╗ ╚╝║║╚╝
//                      ╚╗╔╝   ║║  ║╔╗║   ║║
//                       ║║   ╔╣╠╗ ║╚╝║   ║║
//                       ╚╝   ╚══╝ ╚══╝   ╚╝
//    ╔╗╔═╗                    ╔╗                     ╔╗
//    ║║║╔╝                   ╔╝╚╗                    ║║
//    ║╚╝╝  ╔══╗ ╔══╗ ╔══╗  ╔╗╚╗╔╝  ╔══╗ ╔╗ ╔╗╔╗ ╔══╗ ║║  ╔══╗
//    ║╔╗║  ║║═╣ ║║═╣ ║╔╗║  ╠╣ ║║   ║ ═╣ ╠╣ ║╚╝║ ║╔╗║ ║║  ║║═╣
//    ║║║╚╗ ║║═╣ ║║═╣ ║╚╝║  ║║ ║╚╗  ╠═ ║ ║║ ║║║║ ║╚╝║ ║╚╗ ║║═╣
//    ╚╝╚═╝ ╚══╝ ╚══╝ ║╔═╝  ╚╝ ╚═╝  ╚══╝ ╚╝ ╚╩╩╝ ║╔═╝ ╚═╝ ╚══╝
//                    ║║                         ║║
//                    ╚╝                         ╚╝
//
//    Lead Maintainer: Roman Kutashenko <kutashenko@gmail.com>
//  ────────────────────────────────────────────────────────────

#include <virgil/iot/qt/VSQIoTKit.h>
#include <yiot-iotkit/storages/KSQStorageFS.h>

typedef struct {
    char *dir;

} vs_nix_storage_ctx_t;

//-----------------------------------------------------------------------------
KSQStorageFS::KSQStorageFS() {
    memset(&m_storageImpl, 0, sizeof(m_storageImpl));

    m_storageImpl.file_sz_limit = kFileSizeMax;
    m_storageImpl.impl_func = _funcImpl();

            vs_storage_impl_data_ctx_t
    vs_nix_storage_impl_data_init(const char *dir);
}

/******************************************************************************/
//static void
//_data_to_hex(const uint8_t *_data, uint32_t _len, uint8_t *_out_data, uint32_t *_in_out_len) {
//    const uint8_t hex_str[] = "0123456789abcdef";
//
//            VS_IOT_ASSERT(_in_out_len);
//            VS_IOT_ASSERT(_data);
//            VS_IOT_ASSERT(_out_data);
//            VS_IOT_ASSERT(*_in_out_len >= _len * 2 + 1);
//
//    *_in_out_len = _len * 2 + 1;
//    _out_data[*_in_out_len - 1] = 0;
//    size_t i;
//
//    for (i = 0; i < _len; i++) {
//        _out_data[i * 2 + 0] = hex_str[(_data[i] >> 4) & 0x0F];
//        _out_data[i * 2 + 1] = hex_str[(_data[i]) & 0x0F];
//    }
//}

/******************************************************************************/
//vs_storage_impl_data_ctx_t
//vs_nix_storage_impl_data_init(const char *relative_dir) {
//    vs_nix_storage_ctx_t *ctx = NULL;
//
//    CHECK_NOT_ZERO_RET(relative_dir, NULL);
//
//    ctx = VS_IOT_CALLOC(1, sizeof(vs_nix_storage_ctx_t));
//    CHECK_NOT_ZERO_RET(ctx, NULL);
//
//    ctx->dir = (char *)VS_IOT_CALLOC(1, strlen(relative_dir) + 1);
//    if (NULL == ctx->dir) {
//        VS_LOG_ERROR("Can't allocate memory");
//        VS_IOT_FREE(ctx);
//        return NULL;
//    }
//
//    VS_IOT_STRCPY(ctx->dir, relative_dir);
//
//    // Create path
//    vs_files_create_subdir(relative_dir);
//
//    return ctx;
//}

/******************************************************************************/
vs_status_e
KSQStorageFS::_deinit(vs_storage_impl_data_ctx_t storage_ctx) {
    vs_nix_storage_ctx_t *ctx = (vs_nix_storage_ctx_t *)storage_ctx;

    CHECK_NOT_ZERO_RET(storage_ctx, VS_CODE_ERR_INCORRECT_PARAMETER);
    CHECK_NOT_ZERO_RET(ctx->dir, VS_CODE_ERR_INCORRECT_PARAMETER);

    VS_IOT_FREE(ctx->dir);
    VS_IOT_FREE(ctx);

    return VS_CODE_OK;
}

/******************************************************************************/
vs_storage_file_t
KSQStorageFS::_open(const vs_storage_impl_data_ctx_t storage_ctx, const vs_storage_element_id_t id) {
    vs_nix_storage_ctx_t *ctx = (vs_nix_storage_ctx_t *)storage_ctx;

    CHECK_NOT_ZERO_RET(id, NULL);
    CHECK_NOT_ZERO_RET(storage_ctx, NULL);
    CHECK_NOT_ZERO_RET(ctx->dir, NULL);

    uint32_t len = sizeof(vs_storage_element_id_t) * 2 + 1;
    uint8_t *file = (uint8_t *)VS_IOT_CALLOC(1, len);
    CHECK_NOT_ZERO_RET(file, NULL);

    _data_to_hex(id, sizeof(vs_storage_element_id_t), file, &len);

    return file;
}

/******************************************************************************/
vs_status_e
KSQStorageFS::_sync(const vs_storage_impl_data_ctx_t storage_ctx, const vs_storage_file_t file) {
    vs_status_e res = VS_CODE_ERR_FILE;

    CHECK_NOT_ZERO_RET(file, VS_CODE_ERR_NULLPTR_ARGUMENT);
    CHECK_NOT_ZERO_RET(storage_ctx, VS_CODE_ERR_NULLPTR_ARGUMENT);
    vs_nix_storage_ctx_t *ctx = (vs_nix_storage_ctx_t *)storage_ctx;

    if (vs_files_sync(ctx->dir, (char *)file)) {
        res = VS_CODE_OK;
    }
    return res;
}

/******************************************************************************/
vs_status_e
KSQStorageFS::_close(const vs_storage_impl_data_ctx_t storage_ctx, vs_storage_file_t file) {
    CHECK_NOT_ZERO_RET(file, VS_CODE_ERR_INCORRECT_PARAMETER);

    VS_IOT_FREE(file);

    return VS_CODE_OK;
}

/******************************************************************************/
vs_status_e
KSQStorageFS::_save(const vs_storage_impl_data_ctx_t storage_ctx,
                        const vs_storage_file_t file,
                        size_t offset,
                        const uint8_t *data,
                        size_t data_sz) {
    vs_status_e res = VS_CODE_ERR_FILE_WRITE;

    CHECK_NOT_ZERO_RET(data, VS_CODE_ERR_NULLPTR_ARGUMENT);
    CHECK_NOT_ZERO_RET(storage_ctx, VS_CODE_ERR_NULLPTR_ARGUMENT);
    CHECK_NOT_ZERO_RET(file, VS_CODE_ERR_NULLPTR_ARGUMENT);
    vs_nix_storage_ctx_t *ctx = (vs_nix_storage_ctx_t *)storage_ctx;

    if (vs_files_write(ctx->dir, (char *)file, offset, data, data_sz)) {
        res = VS_CODE_OK;
    }
    return res;
}

/******************************************************************************/
vs_status_e
KSQStorageFS::_load(const vs_storage_impl_data_ctx_t storage_ctx,
                        const vs_storage_file_t file,
                        size_t offset,
                        uint8_t *out_data,
                        size_t data_sz) {
    size_t read_sz;
    vs_status_e res = VS_CODE_ERR_FILE_READ;
    vs_nix_storage_ctx_t *ctx = (vs_nix_storage_ctx_t *)storage_ctx;

    CHECK_NOT_ZERO_RET(out_data, VS_CODE_ERR_INCORRECT_PARAMETER);
    CHECK_NOT_ZERO_RET(storage_ctx, VS_CODE_ERR_INCORRECT_PARAMETER);
    CHECK_NOT_ZERO_RET(file, VS_CODE_ERR_INCORRECT_PARAMETER);
    CHECK_NOT_ZERO_RET(ctx->dir, VS_CODE_ERR_INCORRECT_PARAMETER);

    if (vs_files_read(ctx->dir, (char *)file, offset, out_data, data_sz, &read_sz) && read_sz == data_sz) {
        res = VS_CODE_OK;
    }

    return res;
}

/*******************************************************************************/
ssize_t
KSQStorageFS::_fileSize(const vs_storage_impl_data_ctx_t storage_ctx, const vs_storage_element_id_t id) {
    vs_nix_storage_ctx_t *ctx = (vs_nix_storage_ctx_t *)storage_ctx;
    ssize_t res;
    uint32_t len = sizeof(vs_storage_element_id_t) * 2 + 1;
    uint8_t file[len];

    CHECK_NOT_ZERO_RET(id, VS_CODE_ERR_INCORRECT_PARAMETER);
    CHECK_NOT_ZERO_RET(storage_ctx, VS_CODE_ERR_INCORRECT_PARAMETER);
    CHECK_NOT_ZERO_RET(ctx->dir, VS_CODE_ERR_INCORRECT_PARAMETER);

    _data_to_hex(id, sizeof(vs_storage_element_id_t), file, &len);
    res = vs_files_get_len(ctx->dir, (char *)file);
    return res;
}

/******************************************************************************/
vs_status_e
KSQStorageFS::_del(const vs_storage_impl_data_ctx_t storage_ctx, const vs_storage_element_id_t id) {
    vs_nix_storage_ctx_t *ctx = (vs_nix_storage_ctx_t *)storage_ctx;

    CHECK_NOT_ZERO_RET(id, VS_CODE_ERR_INCORRECT_PARAMETER);
    CHECK_NOT_ZERO_RET(storage_ctx, VS_CODE_ERR_INCORRECT_PARAMETER);
    CHECK_NOT_ZERO_RET(ctx->dir, VS_CODE_ERR_INCORRECT_PARAMETER);

    uint32_t len = sizeof(vs_storage_element_id_t) * 2 + 1;
    uint8_t file[len];

    _data_to_hex(id, sizeof(vs_storage_element_id_t), file, &len);

    return vs_files_remove(ctx->dir, (char *)file) ? VS_CODE_OK : VS_CODE_ERR_FILE_DELETE;
}

//-----------------------------------------------------------------------------
vs_storage_impl_func_t
KSQStorageFS::_funcImpl() {
    vs_storage_impl_func_t impl;
    memset(&impl, 0, sizeof(impl));

    impl.size = _fileSize;
    impl.deinit = _deinit;
    impl.open = _open;
    impl.sync = _sync;
    impl.close = _close;
    impl.save = _save;
    impl.load = _load;
    impl.del = _del;

    return impl;
}

//-----------------------------------------------------------------------------
