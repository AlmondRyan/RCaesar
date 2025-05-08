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
    type ToolbarProps,
    useId,
    webLightTheme,
    Dialog,
    DialogTrigger,
    DialogSurface,
    DialogTitle,
    DialogBody,
    DialogActions
} from "@fluentui/react-components";
import React, {useState} from "react";
import {
    ClearFormatting20Regular,
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

                            <Field label="Text need to encrypt/decrypt">
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
                                        Your input contains non-English characters. Would you like to skip them or delete them?
                                    </DialogBody>
                                    <DialogActions>
                                        <Button appearance="secondary" onClick={() => handleDialogAction('skip')}>Skip</Button>
                                        <Button appearance="primary" onClick={() => handleDialogAction('delete')}>Delete</Button>
                                        <Button appearance="secondary" onClick={() => handleDialogAction('cancel')}>Cancel</Button>
                                    </DialogActions>
                                </DialogSurface>
                            </Dialog>

                            <Dropdown aria-labelledby={dropdownId}
                                      placeholder={"Select an Encrypt Method"}
                                      style={{
                                          marginTop: "24px",
                                          marginRight: "8px"
                                      }}
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
                                style={{
                                    marginTop: "24px",
                                    marginRight: "8px"
                                }}
                                {...DropDownProps}
                            >
                                {decrypt_options.map((d_option) => (
                                    <Option key={d_option} value={d_option}>
                                        {d_option}
                                    </Option>
                                ))}
                            </Dropdown>

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