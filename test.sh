#!/bin/bash
echo ""
echo ""
cat $1
echo ""
echo ""
valgrind --leak-check=full --show-leak-kinds=all ./so_long $1
