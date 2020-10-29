class MainWindow final : public DocumentWindow
{
public:
    MainWindow (const String& name);
    ~MainWindow();

    void closeButtonPressed() override;

private:
    SharedResourcePointer<MainLookAndFeel> mainLookAndFeel;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainWindow)
};
