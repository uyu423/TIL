# ESC to English

vim 애용하는 입장에서 `esc` 키 눌렀을 때 영문 변환 되면 굉장히 편함

Mac Application `Karabiner` 가 필요함

다음 설정 값을 import 한다.

- Karabiner-Elements Preferences - Misc
- Open config folder (~/.config/karabiner) 혹은 `~/.config/karabiner/karabiner.json` 을 직접 수정
- MacBook Touch Bar 모델의 경우 터치바는 보조 키보드로 인식되어 ESC 키가 매핑되지 않을 수 있다. 이 때의 해결방법은 Devices 탭에서 `No product name` 을 활성화해주자. 이게 터치바다.

## 2022-08-19 (with HHKB Hybrid Type-S)
```json
{
    "global": {
        "check_for_updates_on_startup": true,
        "show_in_menu_bar": false,
        "show_profile_name_in_menu_bar": false
    },
    "profiles": [
        {
            "complex_modifications": {
                "parameters": {
                    "basic.simultaneous_threshold_milliseconds": 25,
                    "basic.to_delayed_action_delay_milliseconds": 250,
                    "basic.to_if_alone_timeout_milliseconds": 500,
                    "basic.to_if_held_down_threshold_milliseconds": 250,
                    "mouse_motion_to_scroll.speed": 100
                },
                "rules": [
                    {
                        "description": "ESC to English",
                        "manipulators": [
                            {
                                "from": {
                                    "key_code": "escape",
                                    "modifiers": {
                                        "optional": [
                                            "any"
                                        ]
                                    }
                                },
                                "to": [
                                    {
                                        "key_code": "escape"
                                    }
                                ],
                                "to_if_alone": [
                                    {
                                        "select_input_source": {
                                            "input_source_id": "^com\\.apple\\.keylayout\\.ABC$"
                                        }
                                    }
                                ],
                                "type": "basic"
                            }
                        ]
                    }
                ]
            },
            "devices": [
                {
                    "disable_built_in_keyboard_if_exists": false,
                    "fn_function_keys": [],
                    "identifiers": {
                        "is_keyboard": true,
                        "is_pointing_device": false,
                        "product_id": 256,
                        "vendor_id": 2131
                    },
                    "ignore": false,
                    "manipulate_caps_lock_led": false,
                    "simple_modifications": [
                        {
                            "from": {
                                "key_code": "escape"
                            },
                            "to": [
                                {
                                    "key_code": "escape"
                                }
                            ]
                        },
                        {
                            "from": {
                                "key_code": "left_command"
                            },
                            "to": [
                                {
                                    "key_code": "left_control"
                                }
                            ]
                        },
                        {
                            "from": {
                                "key_code": "left_control"
                            },
                            "to": [
                                {
                                    "key_code": "left_command"
                                }
                            ]
                        },
                        {
                            "from": {
                                "key_code": "right_option"
                            },
                            "to": [
                                {
                                    "key_code": "f13"
                                }
                            ]
                        }
                    ]
                },
                {
                    "disable_built_in_keyboard_if_exists": false,
                    "fn_function_keys": [],
                    "identifiers": {
                        "is_keyboard": true,
                        "is_pointing_device": false,
                        "product_id": 628,
                        "vendor_id": 1452
                    },
                    "ignore": false,
                    "manipulate_caps_lock_led": true,
                    "simple_modifications": []
                },
                {
                    "disable_built_in_keyboard_if_exists": false,
                    "fn_function_keys": [],
                    "identifiers": {
                        "is_keyboard": true,
                        "is_pointing_device": false,
                        "product_id": 834,
                        "vendor_id": 1452
                    },
                    "ignore": false,
                    "manipulate_caps_lock_led": true,
                    "simple_modifications": []
                },
                {
                    "disable_built_in_keyboard_if_exists": false,
                    "fn_function_keys": [],
                    "identifiers": {
                        "is_keyboard": false,
                        "is_pointing_device": true,
                        "product_id": 834,
                        "vendor_id": 1452
                    },
                    "ignore": true,
                    "manipulate_caps_lock_led": false,
                    "simple_modifications": []
                },
                {
                    "disable_built_in_keyboard_if_exists": false,
                    "fn_function_keys": [],
                    "identifiers": {
                        "is_keyboard": true,
                        "is_pointing_device": false,
                        "product_id": 33,
                        "vendor_id": 1278
                    },
                    "ignore": false,
                    "manipulate_caps_lock_led": true,
                    "simple_modifications": [
                        {
                            "from": {
                                "key_code": "left_command"
                            },
                            "to": [
                                {
                                    "key_code": "left_control"
                                }
                            ]
                        },
                        {
                            "from": {
                                "key_code": "left_control"
                            },
                            "to": [
                                {
                                    "key_code": "left_command"
                                }
                            ]
                        },
                        {
                            "from": {
                                "key_code": "right_option"
                            },
                            "to": [
                                {
                                    "key_code": "f13"
                                }
                            ]
                        }
                    ]
                },
                {
                    "disable_built_in_keyboard_if_exists": false,
                    "fn_function_keys": [],
                    "identifiers": {
                        "is_keyboard": false,
                        "is_pointing_device": true,
                        "product_id": 613,
                        "vendor_id": 76
                    },
                    "ignore": true,
                    "manipulate_caps_lock_led": false,
                    "simple_modifications": []
                }
            ],
            "fn_function_keys": [
                {
                    "from": {
                        "key_code": "f1"
                    },
                    "to": [
                        {
                            "consumer_key_code": "display_brightness_decrement"
                        }
                    ]
                },
                {
                    "from": {
                        "key_code": "f2"
                    },
                    "to": [
                        {
                            "consumer_key_code": "display_brightness_increment"
                        }
                    ]
                },
                {
                    "from": {
                        "key_code": "f3"
                    },
                    "to": [
                        {
                            "key_code": "mission_control"
                        }
                    ]
                },
                {
                    "from": {
                        "key_code": "f4"
                    },
                    "to": [
                        {
                            "key_code": "launchpad"
                        }
                    ]
                },
                {
                    "from": {
                        "key_code": "f5"
                    },
                    "to": [
                        {
                            "key_code": "illumination_decrement"
                        }
                    ]
                },
                {
                    "from": {
                        "key_code": "f6"
                    },
                    "to": [
                        {
                            "key_code": "illumination_increment"
                        }
                    ]
                },
                {
                    "from": {
                        "key_code": "f7"
                    },
                    "to": [
                        {
                            "consumer_key_code": "rewind"
                        }
                    ]
                },
                {
                    "from": {
                        "key_code": "f8"
                    },
                    "to": [
                        {
                            "consumer_key_code": "play_or_pause"
                        }
                    ]
                },
                {
                    "from": {
                        "key_code": "f9"
                    },
                    "to": [
                        {
                            "consumer_key_code": "fastforward"
                        }
                    ]
                },
                {
                    "from": {
                        "key_code": "f10"
                    },
                    "to": [
                        {
                            "consumer_key_code": "mute"
                        }
                    ]
                },
                {
                    "from": {
                        "key_code": "f11"
                    },
                    "to": [
                        {
                            "consumer_key_code": "volume_decrement"
                        }
                    ]
                },
                {
                    "from": {
                        "key_code": "f12"
                    },
                    "to": [
                        {
                            "consumer_key_code": "volume_increment"
                        }
                    ]
                }
            ],
            "name": "Default profile",
            "parameters": {
                "delay_milliseconds_before_open_device": 1000
            },
            "selected": true,
            "simple_modifications": [
                {
                    "from": {
                        "key_code": "caps_lock"
                    },
                    "to": [
                        {
                            "key_code": "right_command"
                        }
                    ]
                },
                {
                    "from": {
                        "key_code": "right_command"
                    },
                    "to": [
                        {
                            "key_code": "f13"
                        }
                    ]
                }
            ],
            "virtual_hid_keyboard": {
                "caps_lock_delay_milliseconds": 0,
                "country_code": 0,
                "indicate_sticky_modifier_keys_state": true,
                "keyboard_type": "ansi",
                "mouse_key_xy_scale": 100
            }
        }
    ]
}%
```

## thanks for @rinae (lagacy)

```json
{
    "global": {
        "check_for_updates_on_startup": true,
        "show_in_menu_bar": false,
        "show_profile_name_in_menu_bar": false
    },
    "profiles": [
        {
            "complex_modifications": {
                "parameters": {
                    "basic.simultaneous_threshold_milliseconds": 25,
                    "basic.to_delayed_action_delay_milliseconds": 250,
                    "basic.to_if_alone_timeout_milliseconds": 500,
                    "basic.to_if_held_down_threshold_milliseconds": 250,
                    "mouse_motion_to_scroll.speed": 100
                },
                "rules": [
                    {
                        "description": "ESC to English",
                        "manipulators": [
                            {
                                "from": {
                                    "key_code": "escape",
                                    "modifiers": {
                                        "optional": [
                                            "any"
                                        ]
                                    }
                                },
                                "to": [
                                    {
                                        "key_code": "escape"
                                    }
                                ],
                                "to_if_alone": [
                                    {
                                        "select_input_source": {
                                            "input_source_id": "^com\\.apple\\.keylayout\\.ABC$"
                                        }
                                    }
                                ],
                                "type": "basic"
                            }
                        ]
                    }
                ]
            },
            "devices": [
                {
                    "disable_built_in_keyboard_if_exists": false,
                    "fn_function_keys": [],
                    "identifiers": {
                        "is_keyboard": true,
                        "is_pointing_device": false,
                        "product_id": 256,
                        "vendor_id": 2131
                    },
                    "ignore": false,
                    "manipulate_caps_lock_led": false,
                    "simple_modifications": [
                        {
                            "from": {
                                "key_code": "escape"
                            },
                            "to": {
                                "key_code": "escape"
                            }
                        },
                        {
                            "from": {
                                "key_code": "left_control"
                            },
                            "to": {
                                "key_code": "left_command"
                            }
                        },
                        {
                            "from": {
                                "key_code": "left_command"
                            },
                            "to": {
                                "key_code": "left_control"
                            }
                        }
                    ]
                },
                {
                    "disable_built_in_keyboard_if_exists": false,
                    "fn_function_keys": [],
                    "identifiers": {
                        "is_keyboard": true,
                        "is_pointing_device": false,
                        "product_id": 628,
                        "vendor_id": 1452
                    },
                    "ignore": false,
                    "manipulate_caps_lock_led": true,
                    "simple_modifications": []
                }
            ],
            "fn_function_keys": [
                {
                    "from": {
                        "key_code": "f1"
                    },
                    "to": {
                        "consumer_key_code": "display_brightness_decrement"
                    }
                },
                {
                    "from": {
                        "key_code": "f2"
                    },
                    "to": {
                        "consumer_key_code": "display_brightness_increment"
                    }
                },
                {
                    "from": {
                        "key_code": "f3"
                    },
                    "to": {
                        "key_code": "mission_control"
                    }
                },
                {
                    "from": {
                        "key_code": "f4"
                    },
                    "to": {
                        "key_code": "launchpad"
                    }
                },
                {
                    "from": {
                        "key_code": "f5"
                    },
                    "to": {
                        "key_code": "illumination_decrement"
                    }
                },
                {
                    "from": {
                        "key_code": "f6"
                    },
                    "to": {
                        "key_code": "illumination_increment"
                    }
                },
                {
                    "from": {
                        "key_code": "f7"
                    },
                    "to": {
                        "consumer_key_code": "rewind"
                    }
                },
                {
                    "from": {
                        "key_code": "f8"
                    },
                    "to": {
                        "consumer_key_code": "play_or_pause"
                    }
                },
                {
                    "from": {
                        "key_code": "f9"
                    },
                    "to": {
                        "consumer_key_code": "fastforward"
                    }
                },
                {
                    "from": {
                        "key_code": "f10"
                    },
                    "to": {
                        "consumer_key_code": "mute"
                    }
                },
                {
                    "from": {
                        "key_code": "f11"
                    },
                    "to": {
                        "consumer_key_code": "volume_decrement"
                    }
                },
                {
                    "from": {
                        "key_code": "f12"
                    },
                    "to": {
                        "consumer_key_code": "volume_increment"
                    }
                }
            ],
            "name": "Default profile",
            "parameters": {
                "delay_milliseconds_before_open_device": 1000
            },
            "selected": true,
            "simple_modifications": [],
            "virtual_hid_keyboard": {
                "caps_lock_delay_milliseconds": 0,
                "country_code": 0,
                "keyboard_type": "ansi",
                "mouse_key_xy_scale": 100
            }
        }
    ]
}
```
