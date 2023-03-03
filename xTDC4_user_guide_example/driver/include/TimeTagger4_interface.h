//
// Header file containing structs and #defines specific for TimeTagger4 devices.
// The current driver version for TimeTagger4 devices is %VERSION%
//

/*! \file
 *  \brief The functions provided by the API are declared in
 *  TimeTagger4_interface.h.
 *
 *  The API is a DLL with C linkage.
 */
#ifndef TIMETAGGER4_INTERFACE_H
#define TIMETAGGER4_INTERFACE_H

#include "TDC4_interface.h"

#ifdef __linux__
#include <stdarg.h>
#include <stdint.h>
#define __int32 int32_t
#define __int16 int16_t
typedef signed long int __int64;
typedef unsigned char byte;
#endif

/*! \defgroup constants Constants
 */
/*! \defgroup initialization Initialization
 *@{
 */
/*! \defgroup initfuncts Functions for Initialization
 * @{
 */
/*! \defgroup defclose #defines for timetagger4_close()
 *
 *  timetagger4_close() returns one of the listed values, else
 *  - @link funcerrors TIMETAGGER4_OK @endlink
 *  - @link funcerrors TIMETAGGER4_INVALID_DEVICE @endlink
 */
/*! \defgroup definit #defines for timetagger4_init()
 *
 *  timetagger4_init() returns one of the listed values, else
 *  - @link funcerrors TIMETAGGER4_OK @endlink
 */
/*! \defgroup defdefinpar #defines for timetagger4_get_default_init_parameters()
 *
 *  timetagger4_get_default_init_parameters() returns one of the listed
 *  values, else
 *  - @link funcerrors TIMETAGGER4_OK @endlink
 */
/*!@}*/
/*! \defgroup device Structure timetagger4_device
 */
/*! \defgroup initparamsstruct Structure timetagger4_init_parameters
 *  \brief struct for the initialization of the TimeTagger4
 *
 *  this structure MUST be completely INITIALIZED
 *  @{
 */
/*! \defgroup apiversion #define for version
 */
/*! \defgroup buffertype #defines for buffer_type
 *  \brief type of buffer
 */
/*! \defgroup devicetype #define for device_type
 */
/*!@}*/
/*!@}*/
/*! \defgroup status Status Information
 *  @{
 */
/*! \defgroup statfuncts Functions for Information Retrieval
 *  \brief Functions for getting detailed information about the TimeTagger4
 *  board.
 *
 *  The driver provides functions to retrieve detailed information on the
 *  type of board, it's configuration, settings and state. The information is
 *  split according to its scope and the computational requirements to query the
 *  information from the board.
 *@{
 */
/*! \defgroup defparaminfo #defines for timetagger4_get_param_info()
 *
 *  timetagger4_get_param_info() returns one of the listed values, else
 *  - @link funcerrors TIMETAGGER4_OK @endlink
 *  - @link funcerrors TIMETAGGER4_INVALID_DEVICE @endlink
 */
/*! \defgroup defstatinfo #defines for timetagger4_get_static_info()
 *
 *  timetagger4_get_static_info() returns one of the listed values, else
 *  - @link funcerrors TIMETAGGER4_OK @endlink
 *  - @link funcerrors TIMETAGGER4_INVALID_DEVICE @endlink
 */
/*! \defgroup deffastinfo #defines for timetagger4_get_fast_info()
 *
 *  timetagger4_get_fast_info() returns one of the listed values, else
 *  - @link funcerrors TIMETAGGER4_OK @endlink
 *  - @link funcerrors TIMETAGGER4_INVALID_DEVICE @endlink
 */
/*!@}*/
/*! \defgroup staticinfo Structure timetagger4_static_info
 *  \brief Structure contains static information
 *
 *  This structure contains information about the board that does not change
 *  during run time. It is provided by the function @link statfuncts
 *  timetagger4_get_static_info() @endlink.
 */
/*! \defgroup paraminfo Structure timetagger4_param_info
 *  \brief contains configuration changes
 *
 *  Structure filled by @link statfuncts timetagger4_get_param_info()
 *  @endlink. This structure contains information that change indirectly due to
 *  configuration changes.
 */
/*! \defgroup fastinfo Structure timetagger4_fast_info
 *  \brief contains fast dynamic information
 *
 *  This call returns a structure that contains dynamic information that can
 *  be obtained within a few microseconds.
 */
/*!@}*/
/*! \defgroup configuration Configuration
 *  \brief Configuration of TimeTagger4
 *  @{
 */
/*! \defgroup conffuncts Configuration Functions
 *  \brief Functions for the configuration of TimeTagger4
 *
 *  The device is configured with a configuration structure. The user should
 *  first obtain a structure that contains the default settings of the device
 *  read from an on board ROM, then modify the structure as needed for the user
 *  application and use the result to configure the device.
 * @{
 */
/*! \defgroup defconf #defines for timetagger4_configure()
 *
 * timetagger4_configure() returns one of the listed values, else
 * - @link funcerrors TIMETAGGER4_INVALID_DEVICE @endlink
 */
/*! \defgroup defdefconf #defines for timetagger4_get_default_configuration()
 *
 * timetagger4_get_default_configuration() returns one of the listed
 *values, else
 * - @link funcerrors TIMETAGGER4_OK @endlink
 * - @link funcerrors TIMETAGGER4_INVALID_DEVICE @endlink
 */
/*! \defgroup defcurconf #defines for timetagger4_get_current_configuration()
 *
 * timetagger4_get_current_configuration() returns one of the listed
 * values, else
 * - @link funcerrors TIMETAGGER4_OK @endlink
 * - @link funcerrors TIMETAGGER4_INVALID_DEVICE @endlink
 */
/*!@}*/
/*! \defgroup confstruct Structure timetagger4_configuration
 *  \brief  contains configuration information
 *
 *  This structure contains the configuration information. It is used in
 *  conjunction with
 *  @link conffuncts timetagger4_get_default_configuration(),
 *  timetagger4_get_current_configuration() and timetagger4_configure() @endlink
 *
 *  Internally it uses the structures @link trigger timetagger4_trigger
 *  @endlink and @link tiger timetagger4_tiger_block @endlink
 * @{
 */
/*! \defgroup tdcmode #defines for tdc_mode
 *  \brief tdc_mode can be either grouped or continuous
 */
/*! \defgroup defdcoffset #defines for dc_offset
 *  \brief dc_offset values for various signal standards
 *
 *  used by @link timetagger4_configuration timetagger4_configuration
 *@endlink.
 */
/*!@}*/
/*! \defgroup trigger Structure timetagger4_trigger
 *  \brief contains trigger settings
 */
/*! \defgroup tiger Structure timetagger4_tiger_block
 *  \brief contains settings of timing generator
 * @{
 */
/*! \defgroup deftriggersource #defines for sources
 *  \brief mask for choosing the trigger source
 */
/*!@}*/
/*! \defgroup channel Structure timetagger4_channel
 *  \brief contains TDC channel settings
 */
/*!@}*/
/*! \defgroup runtime Run Time Control
 *  \brief control functions during run time
 *  @{
 */
/*! \defgroup defstartcap #defines for timetagger4_start_capture()
 *
 *  timetagger4_start_capture() returns one of the listed values, else
 *  - @link funcerrors TIMETAGGER4_INVALID_DEVICE @endlink
 */
/*! \defgroup defstopcap #defines for timetagger4_stop_capture()
 *
 *  timetagger4_stop_capture() returns one of the listed values, else
 *  - @link funcerrors TIMETAGGER4_INVALID_DEVICE @endlink
 */
/*! \defgroup defpausecap #defines for timetagger4_pause_capture()
 *
 *  timetagger4_pause_capture() returns one of the listed values, else
 *  - @link funcerrors TIMETAGGER4_INVALID_DEVICE @endlink
 */
/*! \defgroup defcontcap #defines for timetagger4_continue_capture()
 *
 *  timetagger4_continue_capture() returns one of the listed values, else
 *  - @link funcerrors TIMETAGGER4_INVALID_DEVICE @endlink
 */
/*!@}*/
/*! \defgroup mainread Readout
 *  @{
 */
/*! \defgroup readout Functions for Readout
 *  \brief functions for data readout
 *  @{
 */
/*! \defgroup defack #defines for timetagger4_acknowledge()
 *
 *  timetagger4_acknowledge() returns one of the listed values, else
 *  - @link funcerrors TIMETAGGER4_INVALID_DEVICE @endlink
 */
/*! \defgroup defread #defines for timetagger4_read()
 *
 *  timetagger4_read() returns one of the listed values, else
 *  - @link funcerrors TIMETAGGER4_INVALID_DEVICE @endlink
 */
/*!@}*/
/*! \defgroup readin Structure timetagger4_read_in
 *  \brief The parameters of the read commands
 */
/*! \defgroup strucreadout Structure timetagger4_read_out
 * @{
 */
/*! \defgroup deferror #defines for error_code
 *  \brief error code
 */
/*!@}*/
/*!@}*/
/*! \defgroup funcerrors Function Errors
 *
 *  All ERRORS must be positive, because the upper byte is used by
 *  crono_tools
 */
/*! \defgroup packflags Packet Flags
 *  \brief flags of the packet reporting error conditions
 */

// current version of the API
#define TIMETAGGER4_API_VERSION TDC4_API_VERSION

/*! \ingroup constants Constants
 * @{
 */
/*! \brief The number of TDC input channels.
 *
 *  used by
 *  - @link confstruct timetagger4_configuration::dc_offset @endlink
 *  - @link confstruct timetagger4_configuration::channel @endlink
 */
#define TIMETAGGER4_TDC_CHANNEL_COUNT 4
/* unsupported */
#define TIMETAGGER4_LOWRES_CHANNEL_COUNT 3
/*! \brief The number of timing generators. One for each TDC input and one for
 *  the Start input.
 *
 *  used by
 *  - @link confstruct timetagger4_configuration::tiger_block[] @endlink
 */
#define TIMETAGGER4_TIGER_COUNT 5
/*! \brief The number of potential trigger sources for the timing generators.
 *
 *  One for each TDC input, one for the Start input plus some specials. Not
 *  all trigger sources are available on the TimeTagger4.
 *
 *  used by
 *  - @link confstruct timetagger4_configuration::trigger[] @endlink
 */
#define TIMETAGGER4_TRIGGER_COUNT 16 // including "config" for AUTO and ONE
/*!@}*/

/*! \ingroup buffertype
 *@{
 */
#define TIMETAGGER4_BUFFER_ALLOCATE                                            \
    0 //!< either allocated (only option currently)
#define TIMETAGGER4_BUFFER_USE_PHYSICAL 1 //!< or physical
/*!@}*/

/*! \ingroup tdcmode
 *@{
 */
#define TIMETAGGER4_TDC_MODE_GROUPED 0 //!< grouped tdc_mode
#define TIMETAGGER4_TDC_MODE_CONTINUOUS                                        \
    1 //!< continuous tdc_mode: not supported yet
/*!@}*/

/*! \ingroup defdcoffset
 *@{
 */
// INPUT_BASELINE is 1.32V
#define TIMETAGGER4_DC_OFFSET_P_NIM +0.35
#define TIMETAGGER4_DC_OFFSET_P_CMOS +1.18
#define TIMETAGGER4_DC_OFFSET_P_LVCMOS_33 +1.18
#define TIMETAGGER4_DC_OFFSET_P_LVCMOS_25 +1.18
#define TIMETAGGER4_DC_OFFSET_P_LVCMOS_18 +0.90
#define TIMETAGGER4_DC_OFFSET_P_TTL +1.18
#define TIMETAGGER4_DC_OFFSET_P_LVTTL_33 +1.18
#define TIMETAGGER4_DC_OFFSET_P_LVTTL_25 +1.18
#define TIMETAGGER4_DC_OFFSET_P_SSTL_3 +1.18
#define TIMETAGGER4_DC_OFFSET_P_SSTL_2 +1.18
#define TIMETAGGER4_DC_OFFSET_N_NIM -0.35
#define TIMETAGGER4_DC_OFFSET_N_CMOS -1.32
#define TIMETAGGER4_DC_OFFSET_N_LVCMOS_33 -1.32
#define TIMETAGGER4_DC_OFFSET_N_LVCMOS_25 -1.25
#define TIMETAGGER4_DC_OFFSET_N_LVCMOS_18 -0.90
#define TIMETAGGER4_DC_OFFSET_N_TTL -1.32
#define TIMETAGGER4_DC_OFFSET_N_LVTTL_33 -1.32
#define TIMETAGGER4_DC_OFFSET_N_LVTTL_25 -1.25
#define TIMETAGGER4_DC_OFFSET_N_SSTL_3 -1.32
#define TIMETAGGER4_DC_OFFSET_N_SSTL_2 -1.25
/*!@}*/

/*! \ingroup deftriggersource
 *  @{
 */
#define TIMETAGGER4_TRIGGER_SOURCE_S 0x00000001
#define TIMETAGGER4_TRIGGER_SOURCE_A 0x00000002
#define TIMETAGGER4_TRIGGER_SOURCE_B 0x00000004
#define TIMETAGGER4_TRIGGER_SOURCE_C 0x00000008
#define TIMETAGGER4_TRIGGER_SOURCE_D 0x00000010
#define TIMETAGGER4_TRIGGER_SOURCE_S1 0x00000020
#define TIMETAGGER4_TRIGGER_SOURCE_S2 0x00000040
#define TIMETAGGER4_TRIGGER_SOURCE_GATE 0x00000080
#define TIMETAGGER4_TRIGGER_SOURCE_AUTO 0x00004000
#define TIMETAGGER4_TRIGGER_SOURCE_ONE 0x00008000
/*!@}*/

/*! \ingroup packflags
 *  @{
 */
#define TIMETAGGER4_PACKET_FLAG_ODD_HITS                                       \
    1 //!< last 64 bit word contains only one hit
#define TIMETAGGER4_PACKET_FLAG_SLOW_SYNC                                      \
    2 //!< Start pulse distance larger than timestamp counter range
#define TIMETAGGER4_PACKET_FLAG_START_MISSED                                   \
    4 //!< The trigger unit has discarded packets due to full FIFO
#define TIMETAGGER4_PACKET_FLAG_SHORTENED                                      \
    8 //!< The trigger unit has shortend the current packet due to full FIFO
/*! \brief DMA FIFO was full
 *
 *  might not result in dropped packets
 */
#define TIMETAGGER4_PACKET_FLAG_DMA_FIFO_FULL 16
/*! \brief Host buffer was full
 *
 *  might not result in dropped packets
 */
#define TIMETAGGER4_PACKET_FLAG_HOST_BUFFER_FULL 32
/*!@}*/

/*! \ingroup packflags
 *  @{
 */
#define TIMETAGGER4_HIT_FLAG_RISING                                            \
    1 //!< Timestamp of the rising edge, if not set falling edge
#define TIMETAGGER4_HIT_FLAG_TIME_OVERFLOW                                     \
    2 //!< Time since start pulse longer than timestamp counter range
#define TIMETAGGER4_HIT_FLAG_COARSE_TIMESTAMP 4 //!< FPGA coarse time
#define TIMETAGGER4_HIT_FLAG_TDC_MISSING                                       \
    4 //!< TDC has not provided a timestamp, FPGA coarse time given instead
#define TIMETAGGER4_HIT_FLAG_FPGA_MISSING                                      \
    8 //!< FPGA has not seen the stop event, hit may be out of sequence and
      //!< belong to an other group
/*!@}*/

/*! \ingroup funcerrors
 *  @{
 */
/*! \brief no error encountered
 *
 *  used by
 *  - @link defclose timetagger4_close() @endlink
 *  - @link definit timetagger4_init() @endlink
 *  - @link defdefinpar timetagger4_get_default_init_parameters() @endlink
 *  - @link defparaminfo timetagger4_get_param_info() @endlink
 *  - @link defstatinfo timetagger4_get_static_info() @endlink
 *  - @link deffastinfo timetagger4_get_fast_info() @endlink
 *  - @link defdefconf timetagger4_get_default_configuration() @endlink
 *  - @link defcurconf timetagger4_get_current_configuration() @endlink
 */
#define TIMETAGGER4_OK 0
#define TIMETAGGER4_WINDRIVER_NOT_FOUND 1 //!< NOT IMPLEMENTED
#define TIMETAGGER4_DEVICE_NOT_FOUND 2    //!< NOT IMPLEMENTED
#define TIMETAGGER4_NOT_INITIALIZED 3     //!< NOT IMPLEMENTED

/*! \brief invalid pointer
 *
 *  The pointer given to a timetagger4 driver function was not a valid
 *  pointer used by
 *  - @link defclose timetagger4_close() @endlink
 *  - @link defstatinfo timetagger4_get_static_info() @endlink
 *  - @link defparaminfo timetagger4_get_param_info() @endlink
 *  - @link deffastinfo timetagger4_get_fast_info() @endlink
 *  - @link defconf timetagger4_configure() @endlink
 *  - @link defdefconf timetagger4_get_default_configuration() @endlink
 *  - @link defcurconf timetagger4_get_current_configuration() @endlink
 *  - @link defstartcap timetagger4_start_capture() @endlink
 *  - @link defstopcap timetagger4_stop_capture() @endlink
 *  - @link defpausecap timetagger4_pause_capture() @endlink
 *  - @link defcontcap timetagger4_continue_capture() @endlink
 *  - @link defack timetagger4_acknowledge() @endlink
 *  - @link defread timetagger4_read() @endlink
 */
#define TIMETAGGER4_INVALID_DEVICE 5
#define TIMETAGGER4_BUFFER_ALLOC_FAILED 6        //!< NOT IMPLEMENTED
#define TIMETAGGER4_TDC_NO_EDGE_FOUND 7          //!< NOT IMPLEMENTED
#define TIMETAGGER4_INVALID_BUFFER_PARAMETERS 8  //!< NOT IMPLEMENTED
#define TIMETAGGER4_INVALID_CONFIG_PARAMETERS 9  //!< NOT IMPLEMENTED
#define TIMETAGGER4_WINDOW_CALIBRATION_FAILED 10 //!< NOT IMPLEMENTED
#define TIMETAGGER4_HARDWARE_FAILURE 11          //!< NOT IMPLEMENTED
#define TIMETAGGER4_INVALID_TDC_MODE 12          //!< NOT IMPLEMENTED
#define TIMETAGGER4_SYNCHRONIZATION_FAILED 13    //!< NOT IMPLEMENTED
#define TIMETAGGER4_DEVICE_OPEN_FAILED 14        //!< NOT IMPLEMENTED
/*!@}*/

/*! \ingroup defparaminfo
 */
/*! \brief when a capture on a closed card is called
 *
 * else @link funcerrors TIMETAGGER4_OK @endlink
 */
#define TIMETAGGER4_WRONG_STATE 4

#ifdef __cplusplus
extern "C" {
#endif

#if defined(_WIN32) || defined(_WIN64)
#ifdef TIMETAGGER4_DRIVER_EXPORTS
#define TIMETAGGER4_API __declspec(dllexport)
#else
#define TIMETAGGER4_API __declspec(dllimport)
#endif
#else
#define TIMETAGGER4_API
#endif

#define crono_bool_t uint8_t

/*!\ingroup device
 * \brief struct storing properties of the device in use
 */
typedef struct {
    /*! \brief timetagger4
     */
    void *timetagger4;
} timetagger4_device;

/*! \ingroup initparamsstruct
 *  \brief struct for the initialization of the TimeTagger4
 *
 *  this structure MUST be completely INITIALIZED
 */
typedef tdc4_init_parameters timetagger4_init_parameters;

/*! \ingroup initfuncts
 *  \brief Finalizes the driver for this device.
 *
 *  Return values are listed @link defclose here @endlink.
 *  \param *device is type @link timetagger4_device timetagger4_device
 *@endlink
 */
TIMETAGGER4_API int timetagger4_close(timetagger4_device *device);

/*! \ingroup runtime
 *  \brief Start timing generator
 *  \param *device is type @link timetagger4_device timetagger4_device
 *@endlink
 */
TIMETAGGER4_API int timetagger4_start_tiger(timetagger4_device *device);
/*! \ingroup runtime
 *  \brief Stop timing generator
 *  \param *device is type @link timetagger4_device timetagger4_device
 *@endlink
 */
TIMETAGGER4_API int timetagger4_stop_tiger(timetagger4_device *device);
/*! \ingroup runtime
 *  \brief Start data acquisition
 *
 *  Return values are listed @link defstartcap here @endlink.
 *  \param *device is type @link timetagger4_device timetagger4_device
 *@endlink
 */
TIMETAGGER4_API int timetagger4_start_capture(timetagger4_device *device);
/*! \ingroup runtime
 *  \brief  Pause data acquisition
 *
 *  Return values are listed @link defpausecap here @endlink.
 *  \param *device is type @link timetagger4_device timetagger4_device
 *@endlink
 */
TIMETAGGER4_API int timetagger4_pause_capture(timetagger4_device *device);
/*! \ingroup runtime
 *  \brief
 *
 *  Call this to resume data acquisition after a call to
 *  timetagger4_pause_capture(). Return values are listed @link defcontcap here
 *@endlink. \param *device is type @link timetagger4_device timetagger4_device
 *@endlink
 */
TIMETAGGER4_API int timetagger4_continue_capture(timetagger4_device *device);
/*! \ingroup runtime
 *  \brief  stop data acquisition
 *
 *  Return values are listed @link defstopcap here @endlink.
 *  \param *device is type @link timetagger4_device timetagger4_device
 *@endlink
 */
TIMETAGGER4_API int timetagger4_stop_capture(timetagger4_device *device);

/*! \ingroup readout
 *  \brief Acknowledges the processing of the last read block.
 *
 *  This is only necessary if timetagger4_read() is not called with
 *  in.acknowledge_last_read set. This feature allows to either free up partial
 *  DMA space early if there will be no call to timetagtimetagger4_read anytime
 *  soon. It also allows to keep data over multiple calls to timetagger4_read to
 *  avoid unnecessary copying of data. Return values are listed @link defack
 *  here
 *@endlink. \param *device is type @link timetagger4_device timetagger4_device
 *@endlink \param *packet is type crono_packet
 */
TIMETAGGER4_API int timetagger4_acknowledge(timetagger4_device *device,
                                            volatile crono_packet *packet);

/*! \ingroup staticinfo
 *  \brief Structure contains static information
 *
 *  This structure contains information about the board that does not change
 *  during run time. It is provided by the function @link statfuncts
 *  timetagger4_get_static_info() @endlink.
 */
typedef tdc4_static_info timetagger4_static_info;

/*! \ingroup statfuncts
 *  \brief Contains static information.
 *
 *  Gets a structure that contains information about the board that does not
 *  change during run time. Return values are listed @link defstatinfo here
 *  @endlink. \param *device of type timetagger4_device \param *info of type
 *  timetagger4_static_info
 */
TIMETAGGER4_API int timetagger4_get_static_info(timetagger4_device *device,
                                                timetagger4_static_info *info);

/*! \ingroup fastinfo
 *  \brief contains fast dynamic information
 *
 *  This call returns a structure that contains dynamic information that can
 *  be obtained within a few microseconds.
 */
typedef tdc4_fast_info timetagger4_fast_info;

/*! \ingroup statfuncts
 *  \brief Returns fast dynamic information
 *
 *  This call gets a structure that contains dynamic information that can be
 *  obtained within a few microseconds. Return values are listed @link
 *  deffastinfo here @endlink. \param *device of type timetagger4_device \param
 *  *info of type timetagger4_fast_info
 */
TIMETAGGER4_API int timetagger4_get_fast_info(timetagger4_device *device,
                                              timetagger4_fast_info *info);

/*! \ingroup paraminfo
 *  \brief contains configuration changes
 *
 *  Structure filled by @link statfuncts timetagger4_get_param_info()
 *@endlink. This structure contains information that change indirectly due to
 *  configuration changes.
 */
typedef tdc4_param_info timetagger4_param_info;

/*! \ingroup statfuncts
 *  \brief Returns configuration changes
 *
 *  Gets a structure that contains information that changes indirectly due
 *  to configuration changes. Return values are listed @link defparaminfo here
 *  @endlink. \param *device of type timetagger4_device \param *info of type
 *  timetagger4_device
 */
TIMETAGGER4_API int timetagger4_get_param_info(timetagger4_device *device,
                                               timetagger4_param_info *info);

/*! \ingroup readout
 *  \brief Returns most recent error message
 *  \param *device is type timetagger4_device
 */
TIMETAGGER4_API const char *
timetagger4_get_last_error_message(timetagger4_device *device);

/*! \ingroup readout
 *  \brief Returns the type of the device
 *
 *  @link devicetype CRONO_DEVICE_TIMETAGGER4 @endlink
 */
TIMETAGGER4_API int timetagger4_get_device_type(timetagger4_device *device);

/*! \ingroup channel
 *  \brief Contains TDC channel settings
 */
typedef tdc4_channel timetagger4_channel;

/* currently unsupported */
typedef tdc4_lowres_channel timetagger4_lowres_channel;

/*! \ingroup tiger
 *  \brief contains settings of timing generator
 */
typedef tdc4_tiger_block timetagger4_tiger_block;

/* low res trigger config */
/*! \ingroup trigger
 *  \brief contains trigger settings
 */
typedef tdc4_trigger timetagger4_trigger;

/*! \ingroup confstruct Structure timetagger4_configuration
 *  \brief  contains configuration information
 *
 *  This structure contains the configuration information. It is used in
 *  conjunction with
 *  @link conffuncts timetagger4_get_default_configuration(),
 *  timetagger4_get_current_configuration() and timetagger4_configure() @endlink
 *
 *  Internally it uses the structures @link trigger timetagger4_trigger
 *  @endlink and @link tiger timetagger4_tiger_block @endlink
 */
typedef struct {
    /*! \brief The number of bytes occupied by the structure
     */
    int size; //!< The number of bytes occupied by the structure
    /*! \brief A version number
     *
     *  that is increased when the definition of the structure is changed.
     *  The increment can be larger than one to match driver version numbers
     *  or similar. Currently only version 0 is defined.
     */
    int version;
    /*! \brief TDC mode.
     *
     *  Can be grouped or continuous. Currently supported: grouped.
     *  Currently only TIMETAGGER4_TDC_MODE_GROUPED is supported.
     *  This is set per default by timetagger4_get_current_configuration()
     *  and should be left unchanged.
     */
    int tdc_mode;
    /*! \brief Not applicable for TimeTagger4
     *
     *
     */
    crono_bool_t start_rising;
    /*! \brief Set DAC channels for S, A - D.
     *
     *  dc_offset[0]     : threshold for channel Start
     *
     *  dc_offset[1 - 4] : threshold for channels A - D
     *
     *  Supported range is -1.32V to +1.18V. This should be close to 50%
     *  of the height of the input pulse. Examples for various signaling
     *  standards are defined as follows @link defdcoffset #defines for
     *  dc_offset @endlink. The inputs are AC coupled. Thus, the
     *  absolute voltage is not important for pulse inputs. It is the relative
     *  pulse amplitude that causes the input circuits to switch. dc_offset
     *  must be set to the relative switching voltage for the input standard
     *  in use. If the pulses are negative, a negative switching threshold
     *  must be set and vice versa.
     */
    double dc_offset[TIMETAGGER4_TDC_CHANNEL_COUNT + 1];
    timetagger4_trigger
        trigger[TIMETAGGER4_TRIGGER_COUNT]; //!< Configuration of external
                                            //!< trigger sources
    timetagger4_tiger_block
        tiger_block[TIMETAGGER4_TIGER_COUNT]; //!< configuration of the
                                              //!< timing generator (TiGeR)
    timetagger4_channel
        channel[TIMETAGGER4_TDC_CHANNEL_COUNT]; //!< configure polaritiy,
                                                //!< type and threshold for
                                                //!< the TDC channels
    timetagger4_lowres_channel
        lowres_channel[TIMETAGGER4_LOWRES_CHANNEL_COUNT]; // Not applicable
                                                          // for TimeTagger4

    int auto_trigger_period;
    /** \brief Create a trigger either periodically or randomly.
     *
     *  There are two parameters M = @link auto_trigger_period
     *  auto_trigger_period @endlink and N = @link
     *  auto_trigger_random_exponent auto_trigger_random_exponent @endlink
     *  that result in a distance between triggers of T clock cycles.
     *
     *          T = 1 + M + [1...2^N]
     *
     *          0 <= M < 2^32
     *
     *          0 <= N < 32
     *
     *  There is no enable or reset as the usage of this trigger can be
     *  configured in the TiGer block channel source field.
     */
    int auto_trigger_random_exponent;
    ///@}

} timetagger4_configuration;

/*! \ingroup conffuncts
 *  \brief Gets default configuration.
 *
 *  Copies the default configuration to the specified config pointer. Return
 *  values are listed @link defdefconf here @endlink. \param *device of type
 *  timetagger4_device \param *config of type timetagger4_configuration
 */
TIMETAGGER4_API int
timetagger4_get_default_configuration(timetagger4_device *device,
                                      timetagger4_configuration *config);
/*! \ingroup conffuncts
 *  \brief Gets current configuration.
 *
 *  Copies the current configuration to the specified config pointer. Return
 *  values are listed @link defcurconf here @endlink. \param *device of type
 *  timetagger4_device \param *config of type timetagger4_configuration
 */
TIMETAGGER4_API int
timetagger4_get_current_configuration(timetagger4_device *device,
                                      timetagger4_configuration *config);
/*! \ingroup conffuncts
 *  \brief Configures the TimeTagger4 device
 *
 *  Return values are listed @link defconf here @endlink.
 *  \param *device of type timetagger4_device
 *  \param *config of type timetagger4_configuration
 */
/* the config information is copied, so can be changed after the called */
TIMETAGGER4_API int timetagger4_configure(timetagger4_device *device,
                                          timetagger4_configuration *config);

/*! \ingroup initfuncts
 *  \brief Returns the number of boards present in the system that are
 *  supported by this driver. \param *error_code is type int \param
 *  **error_message is type const char
 */
TIMETAGGER4_API int timetagger4_count_devices(int *error_code,
                                              const char **error_message);

/*! \ingroup initfuncts
 * @{
 */
/*! \brief Sets up the standard parameters
 *
 *  Sets up the standard parameters. Gets a set of default parameters for
 *  timetagger4_init() @endlink . This must always be used to initialize the
 *  @link initparamsstruct timetagger4_init_parameter() @endlink structure.
 *  Return values are listed @link defdefinpar here @endlink. \param init is
 *  type *timetagger4_init_parameters
 */
TIMETAGGER4_API int
timetagger4_get_default_init_parameters(timetagger4_init_parameters *init);
/*! \brief Opens and initializes the TimeTagger4 board with the given index.
 *
 *  With error_code and error_message the user must provide pointers to
 *  buffers where error information should be written by the driver. Return
 *  values are listed @link definit here @endlink. \param *params type
 *  timetagger4_init_parameters \param *error_code is type int \param
 *  **error_message is type char. The buffer for the error message has to
 *  contain at least 80 chars.
 */
TIMETAGGER4_API timetagger4_device *
timetagger4_init(timetagger4_init_parameters *params, int *error_code,
                 const char **error_message);
/*!@}*/

/*! \ingroup readin
 *  \brief The parameters of the read commands
 */
typedef tdc4_read_in timetagger4_read_in;

/*! \ingroup strucreadout
 *  \brief struct for the read out of the packets
 */
typedef tdc4_read_out timetagger4_read_out;

/*! \ingroup readout
 *  \brief Return a pointer to an array of captured data in read_out. The
 *  result can contain any number of packets of type timetagger4_packet. read_in
 *  provides parameters to the driver. A call to this method automatically
 *  allows the driver to reuse the memory returned in the previous call if
 *  read_in.acknowledge_last_read is set. Returns an error code as defined in
 *  the structure timetagger4_read_out. \param *device is type
 *  timetagger4_device \param *in is type timetagger4_read_in \param *out is
 *  type timetagger4_read_out
 */
TIMETAGGER4_API int timetagger4_read(timetagger4_device *device,
                                     timetagger4_read_in *in,
                                     timetagger4_read_out *out);

/*! \ingroup statfuncts
 *  \brief Returns the driver version, same format as
 *  timetagger4_static_info::driver_revision. This function does not require
 *  a TimeTagger4 board to be present.
 */
TIMETAGGER4_API int timetagger4_get_driver_revision();

/*! \ingroup statfuncts
 *  \brief Returns the driver version including SVN build revision as a
 *  string. This function does not require a TimeTagger4 board to be present.
 */
TIMETAGGER4_API const char *timetagger4_get_driver_revision_str();
#ifdef __cplusplus
}
#endif

#endif