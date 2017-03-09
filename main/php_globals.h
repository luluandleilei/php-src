/*
   +----------------------------------------------------------------------+
   | PHP Version 7                                                        |
   +----------------------------------------------------------------------+
   | Copyright (c) 1997-2017 The PHP Group                                |
   +----------------------------------------------------------------------+
   | This source file is subject to version 3.01 of the PHP license,      |
   | that is bundled with this package in the file LICENSE, and is        |
   | available through the world-wide-web at the following url:           |
   | http://www.php.net/license/3_01.txt                                  |
   | If you did not receive a copy of the PHP license and are unable to   |
   | obtain it through the world-wide-web, please send a note to          |
   | license@php.net so we can mail you a copy immediately.               |
   +----------------------------------------------------------------------+
   | Author: Zeev Suraski <zeev@zend.com>                                 |
   +----------------------------------------------------------------------+
*/

/* $Id$ */

#ifndef PHP_GLOBALS_H
#define PHP_GLOBALS_H

#include "zend_globals.h"

typedef struct _php_core_globals php_core_globals;

#ifdef ZTS
# define PG(v) ZEND_TSRMG(core_globals_id, php_core_globals *, v)
extern PHPAPI int core_globals_id;
#else
# define PG(v) (core_globals.v)
extern ZEND_API struct _php_core_globals core_globals;
#endif

/* Error display modes */
#define PHP_DISPLAY_ERRORS_STDOUT	1
#define PHP_DISPLAY_ERRORS_STDERR	2

/* Track vars */
#define TRACK_VARS_POST		0
#define TRACK_VARS_GET		1
#define TRACK_VARS_COOKIE	2
#define TRACK_VARS_SERVER	3
#define TRACK_VARS_ENV		4
#define TRACK_VARS_FILES	5
#define TRACK_VARS_REQUEST	6

struct _php_tick_function_entry;

typedef struct _arg_separators {
	char *output;
	char *input;
} arg_separators;

struct _php_core_globals {
	zend_bool implicit_flush;   //�Ƿ�Ҫ��php�������ÿ�������֮���Զ�ˢ������

	zend_long output_buffering; //�����������С(�ֽ�)

	zend_bool enable_dl;    //�Ƿ�����ʹ��dl()������dl()�������ڽ�PHP��Ϊapacheģ�鰲װʱ����Ч��

	char *output_handler;   //�����нű�������ض���һ�������������

	char *unserialize_callback_func;    //��������л���������Ҫʵ����һ��δ������࣬����ָ���Ļص��������Ը�δ�������������Ϊ������unserialize()����
	zend_long serialize_precision;  //�������ͺ�˫�������������л��洢ʱ�ľ���(��Чλ��)��

	zend_long memory_limit; //һ���ű����ܹ����뵽������ڴ��ֽ���(������K��M��Ϊ��λ)��
	zend_long max_input_time;    //ÿ���ű�������������(POST, GET, upload)���������ʱ��(��)

	zend_bool track_errors; //�Ƿ��ڱ���$php_errormsg�б������һ������򾯸���Ϣ
	zend_bool display_errors; //�Ƿ񽫴�����Ϣ��Ϊ�����һ������ʾ
	zend_bool display_startup_errors; //�Ƿ���ʾPHP����ʱ�Ĵ���
	zend_bool log_errors;  //�Ƿ�����־�ļ����¼���󣬾����������¼ȡ����error_logָ��
	zend_long      log_errors_max_len; //���ô�����־�и��ӵ��������Ϣ������Ĵ���Դ����󳤶�
	zend_bool ignore_repeated_errors; //��¼������־ʱ�Ƿ�����ظ��Ĵ�����Ϣ
	zend_bool ignore_repeated_source; //�Ƿ��ں����ظ��Ĵ�����Ϣʱ�����ظ��Ĵ���Դ
	zend_bool report_memleaks; //�Ƿ񱨸��ڴ�й©
	char *error_log; //��������־��¼���ĸ��ļ���

	char *doc_root; //PHP�ġ���Ŀ¼��
	char *user_dir; //����php��ʹ��/~username �򿪽ű�ʱ���ĸ�Ŀ¼��ȥ��
	char *include_path; //ָ��һ��Ŀ¼����require()��include()��fopen_with_path()����ȥѰ��
	char *open_basedir; //��php��������������ļ�(�����ļ�����)�������ڴ���Ŀ¼�б���
	char *extension_dir; //�����չ��(ģ��)��Ŀ¼��Ҳ����php����Ѱ�Ҷ�̬��չģ���Ŀ¼
	char *php_binary;
	char *sys_temp_dir;

	char *upload_tmp_dir; //�ļ��ϴ�ʱ����ļ�����ʱĿ¼
	zend_long upload_max_filesize; //�����ϴ����ļ������ߴ�

	char *error_append_string; //���ڴ�����Ϣ��������ַ���
	char *error_prepend_string; //���ڴ�����Ϣǰ������ַ���

	char *auto_prepend_file; //ָ�������ļ�֮ǰ�Զ��������ļ���
	char *auto_append_file; //ָ�������ļ�֮���Զ��������ļ���

	char *input_encoding;
	char *internal_encoding;
	char *output_encoding;

	arg_separators arg_separator; //php��������URL�������ָ������ķָ���

	char *variables_order; //phpע��Environment��GET��POST��Cookie��Server������˳��

	HashTable rfc1867_protected_variables; //RFC1867�����ı���������main/rfc1867.c�ļ������õ��˱���

	short connection_status; //����״̬��������״̬���������жϣ���ʱ
	short ignore_user_abort; //�Ƿ�ʹ���û���ֹ�����Ҳ��������������

	unsigned char header_is_being_sent; //�Ƿ�ͷ��Ϣ���ڷ���

	zend_llist tick_functions; //����main/php_ticks.c�ļ������õ����˴�����ĺ�����register_trick_function�Ⱥ��������õ�

	zval http_globals[6];  //���GET��POST��SERVER����Ϣ

	zend_bool expose_php; //�Ƿ�չʾphp����Ϣ

	zend_bool register_argc_argv; //�Ƿ�����$argv��$argcȫ�ֱ���(������GET��������Ϣ)
	zend_bool auto_globals_jit; //�Ƿ����ʹ�õ�$_SERVER��$_ENV����ʱ�Ŵ���(�������ڽű�һ����ʱ���Զ�����)

	char *docref_root; 
	char *docref_ext;

	zend_bool html_errors;
	zend_bool xmlrpc_errors;

	zend_long xmlrpc_error_number;

	zend_bool activated_auto_globals[8];

	zend_bool modules_activated;
	zend_bool file_uploads;
	zend_bool during_request_startup;
	zend_bool allow_url_fopen;
	zend_bool enable_post_data_reading;
	zend_bool report_zend_debug;

	int last_error_type;
	char *last_error_message;
	char *last_error_file;
	int  last_error_lineno;

	char *php_sys_temp_dir;

	char *disable_functions;
	char *disable_classes;
	zend_bool allow_url_include;
#ifdef PHP_WIN32
	zend_bool com_initialized;
#endif
	zend_long max_input_nesting_level;
	zend_long max_input_vars;
	zend_bool in_user_include;

	char *user_ini_filename;
	zend_long user_ini_cache_ttl;

	char *request_order;

	zend_bool mail_x_header;
	char *mail_log;

	zend_bool in_error_log;

#ifdef PHP_WIN32
	zend_bool windows_show_crt_warning;
#endif
};


#endif /* PHP_GLOBALS_H */

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 */
