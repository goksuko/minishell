#ifndef PARSER_H
# define PARSER_H

# include "lexer.h"

typedef struct s_procs
{
    int         index;        // Process index
    int         proc_count;   // Number of processes
    int         token_count;  // Number of tokens
    char        *cmd;         // Command string
    bool        cmd_flag;     // Flag for command status
    char        **str;        // Arguments for the command
    char        **redir;      // Redirection strings
    char        **hd;         // Here-document strings
    int         red_count;    // Number of redirections
    int         hd_count;     // Number of here-documents
    int         hd_fd;        // File descriptor for here-doc
    bool        hd_last;      // Flag for last here-doc
    bool        tilde;        // Tilde expansion flag
} t_procs;

typedef struct s_parser
{
    bool				multi_proc_b; // Flag for multiple processes
	struct s_token		*tokens;
    char				***proc_arrs;  // Array of process argument arrays
    int					start;         // Starting index for processing
    int					num_processes;    // Number of processes
    t_procs				**process;     // Array of process pointers
    char				*exit_str;     // Exit string
    int					exit_stat;     // Exit status
    struct s_parser		*next;     // Pointer to the next parser
} t_parser;

#endif