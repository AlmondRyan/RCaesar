// ============ App.tsx =================== TypeScript JSX ===================== //
// Copyright (c) 2025 Remimwen (Almond "NvKopres" Ryan)
// ============================================================================= //

import {
    Button,
    Dropdown,
    type DropdownProps,
    Field,
    FluentProvider,
    Input,
    Menu,
    MenuButton,
    MenuDivider,
    MenuItem,
    MenuList,
    MenuPopover,
    MenuTrigger,
    MessageBar,
    MessageBarBody,
    MessageBarTitle,
    Option,
    Tab,
    TabList,
    type TabValue,
    Toolbar,
    ToolbarButton,
    ToolbarDivider,
    Text,
    type ToolbarProps,
    useId,
    webLightTheme,
    Dialog,
    DialogTrigger,
    DialogSurface,
    DialogTitle,
    DialogBody,
    DialogActions, SpinButton
} from "@fluentui/react-components";
import React, {useState} from "react";
import {
    ClearFormatting24Regular,
    MoreHorizontal24Filled,
    TextCaseTitle24Regular
} from "@fluentui/react-icons";

interface Props {
    DropDownProps: Partial<DropdownProps>;
    ToolBarProps: Partial<ToolbarProps>
}

function App({DropDownProps, ToolBarProps}: Props) {
    const [selectedTab, setSelectedTab] = useState<TabValue>('main');
    const [inputText, setInputText] = useState('');
    const [showDialog, setShowDialog] = useState(false);
    const [showWarning, setShowWarning] = useState(false);
    const [warningMessage, setWarningMessage] = useState('');
    const [selectedEncrypt, setSelectedEncrypt] = useState<string | undefined>(undefined);
    const [selectedDecrypt, setSelectedDecrypt] = useState<string | undefined>(undefined);
    const [groupSize, setGroupSize] = React.useState<number>(0);
    const [focusedIndex, setFocusedIndex] = React.useState<number | null>(null);

    const handleInputChange = (e: React.ChangeEvent<HTMLInputElement>) => {
        const value = e.target.value;
        setInputText(value);
        if (!/^[a-zA-Z]*$/.test(value)) {
            setShowDialog(true);
        }
    };

    const handleDialogAction = (action: 'skip' | 'delete' | 'cancel') => {
        if (action === 'skip') {
            setWarningMessage('You are choosing skip the non-English characters. The engine should work as you want, but I won\'t warranty you the engine have no errors.');
            setShowWarning(true);
        } else if (action === 'cancel') {
            setWarningMessage('Remember your input text has non-English characters!');
            setShowWarning(true);
        } else if (action === 'delete') {
            setInputText(inputText.replace(/[^a-zA-Z]/g, ''));
            setShowWarning(false);
        }
        setShowDialog(false);
    };

    const dropdownId = useId("dropdown-default");

    const encrypt_options = [
        "Basic",
        "Increasing",
        "Group",
        "Multi Encrypt Sheet",
        "Multi Encrypt Sheet and Grouped",
        "Use Word as Encrypt Sheet",
        "---"
    ];

    const decrypt_options = [
        "Basic",
        "Increasing",
        "Force",
        "---"
    ];

    return (
        <FluentProvider theme={webLightTheme}>
            <div style={{display: 'flex', height: '100vh', width: '100vw'}}>
                <TabList
                    vertical
                    selectedValue={selectedTab}
                    onTabSelect={(_, {value}) => setSelectedTab(value)}
                    style={{width: '200px', padding: '16px'}}
                >
                    <Tab value="main">Main</Tab>
                    <Tab value="settings" /* style={{marginTop: 'auto'}} */>Settings</Tab>
                </TabList>

                <div style={{flex: 1, display: 'flex', flexDirection: 'column', width: '100%'}}>
                    <Toolbar aria-label="Default" {...ToolBarProps}>
                        <ToolbarButton
                            aria-label={"Remove Unsupported Characters"}
                            icon={<ClearFormatting24Regular/>}
                        />
                        <ToolbarButton
                            aria-label={"Language"}
                            icon={<TextCaseTitle24Regular/>}
                        />
                        <ToolbarDivider/>
                        <Menu>
                            <MenuTrigger>
                                <ToolbarButton aria-label="More" icon={<MoreHorizontal24Filled/>}/>
                            </MenuTrigger>

                            <MenuPopover>
                                <MenuList>
                                    <MenuItem>Learn Each Encryption</MenuItem>
                                    <MenuItem>Learn Each Decryption</MenuItem>
                                    <MenuDivider/>
                                    <MenuItem>Learn Caesar Password</MenuItem>
                                    <MenuDivider/>
                                    <MenuItem>Help</MenuItem>
                                </MenuList>
                            </MenuPopover>
                        </Menu>
                    </Toolbar>

                    {selectedTab === 'main' && (
                        <div style={{padding: '16px', flex: 1}}>
                            {showWarning && (
                                <MessageBar intent="warning" style={{marginBottom: '16px'}}>
                                    <MessageBarBody>
                                        <MessageBarTitle>{warningMessage}</MessageBarTitle>
                                    </MessageBarBody>
                                </MessageBar>
                            )}

                            <Field label="Text need to encrypt/decrypt"
                            style={{width: "50%"}}>
                                <Input
                                    value={inputText}
                                    onChange={handleInputChange}
                                    onBlur={(e) => handleInputChange(e as React.ChangeEvent<HTMLInputElement>)}
                                />
                            </Field>

                            <Dialog open={showDialog}>
                                <DialogSurface>
                                    <DialogTitle>Non-English Characters Detected</DialogTitle>
                                    <DialogBody>
                                        Your input contains non-English characters. Would you like to skip them or
                                        delete them?
                                    </DialogBody>
                                    <DialogActions>
                                        <Button appearance="secondary"
                                                onClick={() => handleDialogAction('skip')}>Skip</Button>
                                        <Button appearance="primary"
                                                onClick={() => handleDialogAction('delete')}>Delete</Button>
                                        <Button appearance="secondary"
                                                onClick={() => handleDialogAction('cancel')}>Cancel</Button>
                                    </DialogActions>
                                </DialogSurface>
                            </Dialog>

                            <Dropdown
                                aria-labelledby={dropdownId}
                                placeholder={"Select an Encrypt Method"}
                                defaultValue={'---'}
                                // disabled={selectedDecrypt !== '---'}
                                style={{
                                    marginTop: "24px",
                                    marginRight: "8px"
                                }}
                                onOptionSelect={(e, data) => setSelectedEncrypt(data.optionValue)}
                                {...DropDownProps}
                            >
                                {encrypt_options.map((e_option) => (
                                    <Option key={e_option} value={e_option}>
                                        {e_option}
                                    </Option>
                                ))}
                            </Dropdown>

                            <Dropdown
                                aria-labelledby={dropdownId}
                                placeholder={"Select an Decrypt Method"}
                                defaultValue={'---'}
                                // disabled={selectedEncrypt !== '---'}
                                style={{
                                    marginTop: "24px",
                                    marginRight: "8px"
                                }}
                                onOptionSelect={(e, data) => setSelectedDecrypt(data.optionValue)}
                                {...DropDownProps}
                            >
                                {decrypt_options.map((d_option) => (
                                    <Option key={d_option} value={d_option}>
                                        {d_option}
                                    </Option>
                                ))}
                            </Dropdown>

                            {selectedEncrypt === 'Basic' && (
                                <div style={{marginTop: "16px"}}>
                                    <Text>Move Steps </Text>
                                    <SpinButton label="Move Steps" defaultValue={1} min={1} max={1000}/>
                                </div>
                            )}

                            {selectedEncrypt === 'Increasing' && (
                                <div style={{marginTop: "16px"}}>
                                    <Text>Initial Move Steps </Text>
                                    <SpinButton label="Initial Move Steps" defaultValue={1} min={1} max={1000}/>
                                </div>
                            )}

                            {selectedEncrypt === 'Group' && (
                                <div style={{marginTop: "16px"}}>
                                    <div style={{display: 'flex', alignItems: "center", marginBottom: "12px"}}>
                                        <Text style={{marginRight: "8px"}}>Group Size</Text>
                                        <SpinButton
                                            label="Group Size"
                                            value={groupSize}
                                            onChange={(_, data) => setGroupSize(Number(data.value))}
                                            min={1}
                                            max={1000}
                                        />
                                    </div>

                                    {groupSize > 0 && inputText && (
                                        <div style={{display: 'flex', gap: '16px'}}>
                                            <div style={{display: 'flex', flexWrap: 'wrap', gap: '8px'}}>
                                                {Array.from({length: Math.ceil(inputText.length / groupSize)}, (_, index) => {
                                                    const group = inputText.slice(index * groupSize, (index + 1) * groupSize);
                                                    const isFocused = focusedIndex === index;

                                                    return (
                                                        <div
                                                            key={index}
                                                            style={{
                                                                padding: '8px 12px',
                                                                borderRadius: '8px',
                                                                border: `2px solid ${isFocused ? '#0078D4' : '#ccc'}`,
                                                                backgroundColor: isFocused ? '#E5F1FB' : '#f5f5f5',
                                                                fontFamily: 'Consolas',
                                                                minWidth: '40px',
                                                                textAlign: 'center'
                                                            }}
                                                        >
                                                            {group}
                                                        </div>
                                                    );
                                                })}
                                            </div>

                                            <div style={{display: 'flex', flexDirection: 'column', gap: '8px'}}>
                                                {Array.from({length: Math.ceil(inputText.length / groupSize)}, (_, index) => (
                                                    <SpinButton
                                                        key={index}
                                                        label={`Value ${index + 1}`}
                                                        defaultValue={1}
                                                        min={0}
                                                        max={100}
                                                        onFocus={() => setFocusedIndex(index)}
                                                        onBlur={() => setFocusedIndex(null)}
                                                    />
                                                ))}
                                            </div>
                                        </div>
                                    )}
                                </div>
                            )}

                            <Field label="Result" style={{marginTop: '16px'}}>
                                <div style={{display: 'flex', alignItems: 'center'}}>
                                    <Input/>
                                    <Button style={{marginLeft: '8px'}}>Copy</Button>
                                </div>
                            </Field>

                            <Button
                                style={{marginTop: '16px'}}
                                appearance={"primary"}
                            >Process!</Button>
                        </div>
                    )}
                </div>
            </div>
        </FluentProvider>
    );
};

export default App;