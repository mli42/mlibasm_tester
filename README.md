# mlibasm_tester

<p align="center">
  <img src="https://github.com/mli42/mlibasm_tester/blob/master/mlibasm.png"
       title="mlibasm img">
</p>

## Usage

Go in your libasm repository and :

```bash
git clone --recurse-submodules https://github.com/mli42/mlibasm_tester.git &&
cd ./mlibasm_tester/ && ./do.sh
```

To test `errno` on `ft_strdup` : `./strdup_kill` and see if `errno == ENOMEM`

Checks leaks by using `/usr/bin/leaks`

`#define CHECKLEAKS 0` (in `mlibasm.h`) to disable it

## Functions
- [ ] ft_strlen
- [ ] ft_strcpy
- [ ] ft_strcmp
- [x] ft_write
- [x] ft_read
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
