#!/usr/bin/env bash
python3 -m venv .venv
VENV_DIR=".venv"

if [ ! -d "$VENV_DIR" ]; then
    echo "❌ Окружение не найдено: $VENV_DIR"
    echo "Создай его командой:"
    echo "  python3 -m venv .venv"
    exit 1
fi

echo "✔ Активирую виртуальное окружение..."
source "$VENV_DIR/bin/activate"

if [ -n "$VIRTUAL_ENV" ]; then
    echo "✔ Окружение активировано: $VIRTUAL_ENV"
else
    echo "❌ Ошибка активации окружения"
fi
