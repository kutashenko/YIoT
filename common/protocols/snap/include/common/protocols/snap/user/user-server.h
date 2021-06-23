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

#ifndef YIOT_SNAP_SERVICES_PC_SERVER_H
#define YIOT_SNAP_SERVICES_PC_SERVER_H

#if PC_SERVER

#include <virgil/iot/protocols/snap/snap-structs.h>
#include <common/protocols/snap/user/user-structs.h>
#include <common/protocols/snap/user/user-private.h>

#ifdef __cplusplus
namespace VirgilIoTKit {
extern "C" {
#endif

typedef vs_status_e (*vs_snap_user_get_state_server_cb_t)(const vs_netif_t *netif,
                                                          char *state,
                                                          const uint16_t buf_sz,
                                                          uint16_t *state_sz);

typedef vs_status_e (*vs_snap_user_command_server_cb_t)(const vs_netif_t *netif,
                                                        vs_mac_addr_t sender_mac,
                                                        const char *command_json);

/** PC server implementations
 *
 * \note Any callback can be NULL. In this case, there will be no actions with requests.
 *
 */
typedef struct {
    vs_snap_user_get_state_server_cb_t get_data; /**< Get data to send it over snap */
    vs_snap_user_command_server_cb_t pc_cmd;     /**< PC Command */
} vs_snap_user_server_service_t;

/** PC Server SNAP Service implementation
 *
 * This call returns PC server implementation. It must be called before any PC call.
 *
 * \param[in] impl Snap PC Server functions implementation.
 *
 * \return #vs_snap_service_t PC service description. Use this pointer to call #vs_snap_register_service.
 */
const vs_snap_service_t *
vs_snap_user_server(vs_snap_user_server_service_t impl);

vs_status_e
vs_snap_user_start_notification(const vs_netif_t *netif);

#ifdef __cplusplus
} // extern "C"
} // namespace VirgilIoTKit
#endif

#endif // PC_SERVER

#endif // YIOT_SNAP_SERVICES_PC_SERVER_H
