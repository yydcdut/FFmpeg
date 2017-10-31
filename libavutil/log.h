/*
 * copyright (c) 2006 Michael Niedermayer <michaelni@gmx.at>
 *
 * This file is part of FFmpeg.
 *
 * FFmpeg is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * FFmpeg is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with FFmpeg; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 */

#ifndef AVUTIL_LOG_H
#define AVUTIL_LOG_H

#include <stdarg.h>
#include "avutil.h"
#include "attributes.h"
#include "version.h"

enum media_ffp_error_type {
    // 0xx
    MEDIA_ERROR_FFP_UNKNOWN = 1,
    // 1xx
    MEDIA_ERROR_FFP_SERVER_DIED = 100,
    // 2xx
    MEDIA_ERROR_FFP_NOT_VALID_FOR_PROGRESSIVE_PLAYBACK = 200,
    // 3xx

    // -xx
    MEDIA_ERROR_FFP_IO          = -1004,
    MEDIA_ERROR_FFP_MALFORMED   = -1007,
    MEDIA_ERROR_FFP_UNSUPPORTED = -1010,
    MEDIA_ERROR_FFP_TIMED_OUT   = -110,

    MEDIA_ERROR_FFP_IJK_PLAYER  = -10000,

    MEDIA_ERROR_FFP_IJK_PLAYER_STREAM_OPEN                  = -10010,//-10010

    MEDIA_ERROR_FFP_IJK_PLAYER_FRAME_QUEUE_INIT_VIDEO       = -10011,//crash
    MEDIA_ERROR_FFP_IJK_PLAYER_FRAME_QUEUE_INIT_SUBTITLE    = -10012,//crash
    MEDIA_ERROR_FFP_IJK_PLAYER_FRAME_QUEUE_INIT_AUDIO       = -10013,//crash
    MEDIA_ERROR_FFP_IJK_PLAYER_PACKET_QUEUE_INIT_ALL        = -10014,//crash
    MEDIA_ERROR_FFP_IJK_PLAYER_CONTINUE_READ_THREAD         = -10015,//crash
    MEDIA_ERROR_FFP_IJK_PLAYER_VIDEO_REFRESH_TID            = -10016,//-10016-->-10010-->crash
    MEDIA_ERROR_FFP_IJK_PLAYER_READ_TID                     = -10017,//-10017-->-10023-->-10010
    MEDIA_ERROR_FFP_IJK_PLAYER_FILE_NAME                    = -10018,//crash
    MEDIA_ERROR_FFP_IJK_PLAYER_AV_MALLOCZ                   = -10019,//-10019-->-10010

    MEDIA_ERROR_FFP_IJK_PLAYER_WAIT_MUTEX                   = -10021,//-10021
    MEDIA_ERROR_FFP_IJK_PLAYER_AVFORMAT_ALLOC_CONTEXT       = -10022,//-10022
    MEDIA_ERROR_FFP_IJK_PLAYER_AVFORMAT_OPEN_INPUT          = -10023,//-10023
    MEDIA_ERROR_FFP_IJK_PLAYER_AVFORMAT_FIND_STREAM_INFO    = -10024,//-10024
    MEDIA_ERROR_FFP_IJK_PLAYER_NO_VIDEO_OR_AUDIO_STREAM     = -10025,//-10025
    MEDIA_ERROR_FFP_IJK_PLAYER_AV_DICT_GET                  = -10026,//-10026
    MEDIA_ERROR_FFP_IJK_PLAYER_AV_COPY_PACKET               = -10027,//-10027
    MEDIA_ERROR_FFP_IJK_PLAYER_AUTO_EXIT                    = -10028,//-10028

    /* stream_component_open */ /* 直接影响 MEDIA_ERROR_FFP_IJK_PLAYER_NO_VIDEO_OR_AUDIO_STREAM(-10025) */
    MEDIA_ERROR_FFP_IJK_PLAYER_AVCODEC_NOT_FIND             = -10031,//-10031-->-10025
    MEDIA_ERROR_FFP_IJK_PLAYER_AVCODEC_OPEN                 = -10032,//-10032-->-10025
    //MEDIA_ERROR_FFP_IJK_PLAYER_AUDIO_OPEN                   = -10033,
    //MEDIA_ERROR_FFP_IJK_PLAYER_AUDIO_DECODER_START          = -10034,
    MEDIA_ERROR_FFP_IJK_PLAYER_OPEN_VIDEO_DECODER           = -10035,//-10035-->第二次crash
    //MEDIA_ERROR_FFP_IJK_PLAYER_VIDEO_DECODER_START          = -10036,
    MEDIA_ERROR_FFP_IJK_PLAYER_AVCODEC_PARAMETERS_TO_CONTEXT= -10037,//-10037-->-10025
    MEDIA_ERROR_FFP_IJK_PLAYER_CONFIGURE_AUDIO_FILTERS      = -10038,//
    MEDIA_ERROR_FFP_IJK_PLAYER_AVCODEC_ALLOC_CONTEXT3       = -10039,//-10039-->-10025
    MEDIA_ERROR_FFP_IJK_PLAYER_STREAM_INDEX                 = -10040,//-10040-->-10025


    //sub err    send type: FFP_MSG_IJK_ERROR
    MEDIA_ERROR_FFP_AOI_INIT     = -12301,// 10023 -> 12301

    MEDIA_ERROR_FFP_AOI_HTTP_OPEN = -12302, //12301
    MEDIA_ERROR_FFP_AOI_HTTP_OPENWL = -12303, // 12302
    MEDIA_ERROR_FFP_AOI_HTTP_OPENWL_FP = -12304,//12303
    MEDIA_ERROR_FFP_AOI_HTTP_OPENWL_TCPOPEN = -12305,//12303
    MEDIA_ERROR_FFP_AOI_HTTP_OPENWL_TCPOPEN_DNS = -12306,//12305
    MEDIA_ERROR_FFP_AOI_HTTP_OPENWL_TCPOPEN_SOCKET = -12307,//12305
    MEDIA_ERROR_FFP_AOI_HTTP_OPENWL_TCPOPEN_CONNET = -12308, //12305

    MEDIA_ERROR_FFP_AOI_HTTP_OPEN_CNTX = -12314,//12302

    MEDIA_ERROR_FFP_AOI_HTTP_CONNECT = -12309,//12302
    MEDIA_ERROR_FFP_AOI_HTTP_CONNECT_TCPWRITE = -12310,//12309
    MEDIA_ERROR_FFP_AOI_HTTP_CONNECT_READHEADER = -12311,//12309
    MEDIA_ERROR_FFP_AOI_HTTP_CONNECT_READHEADER_READ = -12312,//12311
    MEDIA_ERROR_FFP_AOI_HTTP_CONNECT_READHEADER_PROCESS = -12313,//12311

    MEDIA_ERROR_FFP_AOI_PROBE = -12350,// 12301

    MEDIA_ERROR_FFP_AOI_PROBE_AVIOREAD = -12351,//12350  http->tcp

    MEDIA_ERROR_FFP_AOI_PROBE_FORMAT = -12360,//nouse

    MEDIA_ERROR_FFP_AOI_TCPWRITE = -12395,//no  parent
    MEDIA_ERROR_FFP_AOI_TCPWRITE_WAITERR = -12380,//12310
    MEDIA_ERROR_FFP_AOI_TCPWRITE_TIMEOUT = -12381,//12310
    MEDIA_ERROR_FFP_AOI_TCPWRITE_SENDERR = -12382,//12310
    MEDIA_ERROR_FFP_AOI_TCPREAD = -12396,//no  parent
    MEDIA_ERROR_FFP_AOI_TCPREAD_RECVERR = -12383,//12352
    MEDIA_ERROR_FFP_AOI_TCPREAD_TIMEOUT = -12384,//12352
    MEDIA_ERROR_FFP_AOI_TCPREAD_WAITERR = -12385,//12352

    MEDIA_ERROR_FFP_MOV_HEADER = -32300, //10023
    MEDIA_ERROR_FFP_MOV_HEADER_DECR = -32301,//32300
    MEDIA_ERROR_FFP_MOV_HEADER_ERR_READING = -32302,//32300
    MEDIA_ERROR_FFP_MOV_HEADER_MOOV_NOT_FOUND = -32303,//32300
    MEDIA_ERROR_FFP_MOV_HEADER_INVALIDDATA = -32304,//32300
    MEDIA_ERROR_FFP_MOV_HEADER_SIDE_DATE = -32305,//32300

    MEDIA_ERROR_FFP_AVFORMAT_OPEN_INPUT_OK = -998877,//tell java avformat_open_input is ok


};


typedef enum {
    AV_CLASS_CATEGORY_NA = 0,
    AV_CLASS_CATEGORY_INPUT,
    AV_CLASS_CATEGORY_OUTPUT,
    AV_CLASS_CATEGORY_MUXER,
    AV_CLASS_CATEGORY_DEMUXER,
    AV_CLASS_CATEGORY_ENCODER,
    AV_CLASS_CATEGORY_DECODER,
    AV_CLASS_CATEGORY_FILTER,
    AV_CLASS_CATEGORY_BITSTREAM_FILTER,
    AV_CLASS_CATEGORY_SWSCALER,
    AV_CLASS_CATEGORY_SWRESAMPLER,
    AV_CLASS_CATEGORY_DEVICE_VIDEO_OUTPUT = 40,
    AV_CLASS_CATEGORY_DEVICE_VIDEO_INPUT,
    AV_CLASS_CATEGORY_DEVICE_AUDIO_OUTPUT,
    AV_CLASS_CATEGORY_DEVICE_AUDIO_INPUT,
    AV_CLASS_CATEGORY_DEVICE_OUTPUT,
    AV_CLASS_CATEGORY_DEVICE_INPUT,
    AV_CLASS_CATEGORY_NB  ///< not part of ABI/API
}AVClassCategory;

#define AV_IS_INPUT_DEVICE(category) \
    (((category) == AV_CLASS_CATEGORY_DEVICE_VIDEO_INPUT) || \
     ((category) == AV_CLASS_CATEGORY_DEVICE_AUDIO_INPUT) || \
     ((category) == AV_CLASS_CATEGORY_DEVICE_INPUT))

#define AV_IS_OUTPUT_DEVICE(category) \
    (((category) == AV_CLASS_CATEGORY_DEVICE_VIDEO_OUTPUT) || \
     ((category) == AV_CLASS_CATEGORY_DEVICE_AUDIO_OUTPUT) || \
     ((category) == AV_CLASS_CATEGORY_DEVICE_OUTPUT))

struct AVOptionRanges;

/**
 * Describe the class of an AVClass context structure. That is an
 * arbitrary struct of which the first field is a pointer to an
 * AVClass struct (e.g. AVCodecContext, AVFormatContext etc.).
 */
typedef struct AVClass {
    /**
     * The name of the class; usually it is the same name as the
     * context structure type to which the AVClass is associated.
     */
    const char* class_name;

    /**
     * A pointer to a function which returns the name of a context
     * instance ctx associated with the class.
     */
    const char* (*item_name)(void* ctx);

    /**
     * a pointer to the first option specified in the class if any or NULL
     *
     * @see av_set_default_options()
     */
    const struct AVOption *option;

    /**
     * LIBAVUTIL_VERSION with which this structure was created.
     * This is used to allow fields to be added without requiring major
     * version bumps everywhere.
     */

    int version;

    /**
     * Offset in the structure where log_level_offset is stored.
     * 0 means there is no such variable
     */
    int log_level_offset_offset;

    /**
     * Offset in the structure where a pointer to the parent context for
     * logging is stored. For example a decoder could pass its AVCodecContext
     * to eval as such a parent context, which an av_log() implementation
     * could then leverage to display the parent context.
     * The offset can be NULL.
     */
    int parent_log_context_offset;

    /**
     * Return next AVOptions-enabled child or NULL
     */
    void* (*child_next)(void *obj, void *prev);

    /**
     * Return an AVClass corresponding to the next potential
     * AVOptions-enabled child.
     *
     * The difference between child_next and this is that
     * child_next iterates over _already existing_ objects, while
     * child_class_next iterates over _all possible_ children.
     */
    const struct AVClass* (*child_class_next)(const struct AVClass *prev);

    /**
     * Category used for visualization (like color)
     * This is only set if the category is equal for all objects using this class.
     * available since version (51 << 16 | 56 << 8 | 100)
     */
    AVClassCategory category;

    /**
     * Callback to return the category.
     * available since version (51 << 16 | 59 << 8 | 100)
     */
    AVClassCategory (*get_category)(void* ctx);

    /**
     * Callback to return the supported/allowed ranges.
     * available since version (52.12)
     */
    int (*query_ranges)(struct AVOptionRanges **, void *obj, const char *key, int flags);
} AVClass;

/**
 * @addtogroup lavu_log
 *
 * @{
 *
 * @defgroup lavu_log_constants Logging Constants
 *
 * @{
 */

/**
 * Print no output.
 */
#define AV_LOG_QUIET    -8

/**
 * Something went really wrong and we will crash now.
 */
#define AV_LOG_PANIC     0

/**
 * Something went wrong and recovery is not possible.
 * For example, no header was found for a format which depends
 * on headers or an illegal combination of parameters is used.
 */
#define AV_LOG_FATAL     8

/**
 * Something went wrong and cannot losslessly be recovered.
 * However, not all future data is affected.
 */
#define AV_LOG_ERROR    16

/**
 * Something somehow does not look correct. This may or may not
 * lead to problems. An example would be the use of '-vstrict -2'.
 */
#define AV_LOG_WARNING  24

/**
 * Standard information.
 */
#define AV_LOG_INFO     32

/**
 * Detailed information.
 */
#define AV_LOG_VERBOSE  40

/**
 * Stuff which is only useful for libav* developers.
 */
#define AV_LOG_DEBUG    48

/**
 * Extremely verbose debugging, useful for libav* development.
 */
#define AV_LOG_TRACE    56

#define AV_LOG_MAX_OFFSET (AV_LOG_TRACE - AV_LOG_QUIET)

/**
 * @}
 */

/**
 * Sets additional colors for extended debugging sessions.
 * @code
   av_log(ctx, AV_LOG_DEBUG|AV_LOG_C(134), "Message in purple\n");
   @endcode
 * Requires 256color terminal support. Uses outside debugging is not
 * recommended.
 */
#define AV_LOG_C(x) ((x) << 8)

/**
 * Send the specified message to the log if the level is less than or equal
 * to the current av_log_level. By default, all logging messages are sent to
 * stderr. This behavior can be altered by setting a different logging callback
 * function.
 * @see av_log_set_callback
 *
 * @param avcl A pointer to an arbitrary struct of which the first field is a
 *        pointer to an AVClass struct or NULL if general log.
 * @param level The importance level of the message expressed using a @ref
 *        lavu_log_constants "Logging Constant".
 * @param fmt The format string (printf-compatible) that specifies how
 *        subsequent arguments are converted to output.
 */
void av_log(void *avcl, int level, const char *fmt, ...) av_printf_format(3, 4);


/**
 * Send the specified message to the log if the level is less than or equal
 * to the current av_log_level. By default, all logging messages are sent to
 * stderr. This behavior can be altered by setting a different logging callback
 * function.
 * @see av_log_set_callback
 *
 * @param avcl A pointer to an arbitrary struct of which the first field is a
 *        pointer to an AVClass struct.
 * @param level The importance level of the message expressed using a @ref
 *        lavu_log_constants "Logging Constant".
 * @param fmt The format string (printf-compatible) that specifies how
 *        subsequent arguments are converted to output.
 * @param vl The arguments referenced by the format string.
 */
void av_vlog(void *avcl, int level, const char *fmt, va_list vl);

/**
 * Get the current log level
 *
 * @see lavu_log_constants
 *
 * @return Current log level
 */
int av_log_get_level(void);

/**
 * Set the log level
 *
 * @see lavu_log_constants
 *
 * @param level Logging level
 */
void av_log_set_level(int level);

/**
 * Set the logging callback
 *
 * @note The callback must be thread safe, even if the application does not use
 *       threads itself as some codecs are multithreaded.
 *
 * @see av_log_default_callback
 *
 * @param callback A logging function with a compatible signature.
 */
void av_log_set_callback(void (*callback)(void*, int, const char*, va_list));

/**
 * Default logging callback
 *
 * It prints the message to stderr, optionally colorizing it.
 *
 * @param avcl A pointer to an arbitrary struct of which the first field is a
 *        pointer to an AVClass struct.
 * @param level The importance level of the message expressed using a @ref
 *        lavu_log_constants "Logging Constant".
 * @param fmt The format string (printf-compatible) that specifies how
 *        subsequent arguments are converted to output.
 * @param vl The arguments referenced by the format string.
 */
void av_log_default_callback(void *avcl, int level, const char *fmt,
                             va_list vl);

/**
 * Return the context name
 *
 * @param  ctx The AVClass context
 *
 * @return The AVClass class_name
 */
const char* av_default_item_name(void* ctx);
AVClassCategory av_default_get_category(void *ptr);

/**
 * Format a line of log the same way as the default callback.
 * @param line          buffer to receive the formatted line
 * @param line_size     size of the buffer
 * @param print_prefix  used to store whether the prefix must be printed;
 *                      must point to a persistent integer initially set to 1
 */
void av_log_format_line(void *ptr, int level, const char *fmt, va_list vl,
                        char *line, int line_size, int *print_prefix);

/**
 * Format a line of log the same way as the default callback.
 * @param line          buffer to receive the formatted line;
 *                      may be NULL if line_size is 0
 * @param line_size     size of the buffer; at most line_size-1 characters will
 *                      be written to the buffer, plus one null terminator
 * @param print_prefix  used to store whether the prefix must be printed;
 *                      must point to a persistent integer initially set to 1
 * @return Returns a negative value if an error occurred, otherwise returns
 *         the number of characters that would have been written for a
 *         sufficiently large buffer, not including the terminating null
 *         character. If the return value is not less than line_size, it means
 *         that the log message was truncated to fit the buffer.
 */
int av_log_format_line2(void *ptr, int level, const char *fmt, va_list vl,
                        char *line, int line_size, int *print_prefix);


void av_set_notify_msg_callback(void *ctx_ffp,void (*callback)(void*, int, int, void *, int));
void av_set_notify_err_string_callback(void *ctx_ffp,void (*callback)(void*, int, int, void *, int));


void av_notify_msg( int mainerr, int suberr, void *obj, int obj_len);
void av_notify_err_string( int mainerr, int suberr, void *str, int ret);

#if FF_API_DLOG
/**
 * av_dlog macros
 * @deprecated unused
 * Useful to print debug messages that shouldn't get compiled in normally.
 */

#ifdef DEBUG
#    define av_dlog(pctx, ...) av_log(pctx, AV_LOG_DEBUG, __VA_ARGS__)
#else
#    define av_dlog(pctx, ...) do { if (0) av_log(pctx, AV_LOG_DEBUG, __VA_ARGS__); } while (0)
#endif
#endif /* FF_API_DLOG */

/**
 * Skip repeated messages, this requires the user app to use av_log() instead of
 * (f)printf as the 2 would otherwise interfere and lead to
 * "Last message repeated x times" messages below (f)printf messages with some
 * bad luck.
 * Also to receive the last, "last repeated" line if any, the user app must
 * call av_log(NULL, AV_LOG_QUIET, "%s", ""); at the end
 */
#define AV_LOG_SKIP_REPEATED 1

/**
 * Include the log severity in messages originating from codecs.
 *
 * Results in messages such as:
 * [rawvideo @ 0xDEADBEEF] [error] encode did not produce valid pts
 */
#define AV_LOG_PRINT_LEVEL 2

void av_log_set_flags(int arg);
int av_log_get_flags(void);

/**
 * @}
 */

#endif /* AVUTIL_LOG_H */
