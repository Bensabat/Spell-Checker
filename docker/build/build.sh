#!/bin/bash
set -m

bash configure
cd out && cmake .. && cd .. && make &

fg