# mlibasm_tester

## Usage

Go in your libasm repository and :

`git clone --recurse-submodules https://github.com/mli42/mlibasm_tester.git`

To test `errno` on `ft_strdup` : `./strdup_kill` and see if `errno == ENOMEM`

## Functions
- [ ] ft_strlen
- [ ] ft_strcpy
- [ ] ft_strcmp
- [ ] ft_write
- [ ] ft_read
- [ ] ft_strdup

## Bonus (from the piscine)
```c
typedef struct  s_list
{
    void          *data;
    struct s_list *next;
}           t_list;
```
- [ ] ft_atoi_base
- [ ] ft_list_push_front
- [ ] ft_list_size
- [ ] ft_list_sort
- [ ] ft_list_remove_if
