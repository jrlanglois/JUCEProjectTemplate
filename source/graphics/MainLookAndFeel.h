//==============================================================================
class SharedFonts final
{
public:
    SharedFonts() = default;

    struct TypefaceFamily final
    {
        struct Weight final
        {
            Typeface::Ptr thin, ultraLight, light, semiLight,
                          normal, medium, semiBold, bold, extraBold,
                          black, extraBlack, ultraBlack;
        };

        Weight regular, italic;
    };

    /** Loads up the typeface and font instances.

        This will only load up things once by checking
        if the objects are valid or not.
    */
    void initialise();

    static Typeface::Ptr getTypefaceFromFamily (const Font& source, const String& nameToLookFor,
                                                Typeface::Ptr regular,
                                                Typeface::Ptr bold = nullptr,
                                                Typeface::Ptr italic = nullptr,
                                                Typeface::Ptr boldItalic = nullptr);

    static Typeface::Ptr getTypefaceFromFamily (const Font& source, const String& nameToLookFor,
                                                const TypefaceFamily& family);

    TypefaceFamily plex, roboto, robotoMono;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SharedFonts)
};

//==============================================================================
class SharedResources final
{
public:
    SharedResources() = default;

    void initialise();

    SharedFonts sharedFonts;

private:
    bool hasInitialised = false;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SharedResources)
};

//==============================================================================
class MainLookAndFeel final : public LookAndFeel_V4
{
public:
    MainLookAndFeel();

    static void drawTextInRegion (Graphics& g, const Font& f, const String& text, Justification j,
                                  const Rectangle<int>& region, Colour colour = GlobalColours::dustyGrayDark, bool isEnabled = true);

    static Grid createDefaultGrid();

    //==============================================================================
    int getMenuWindowFlags() override { return 0; }
    int getAlertBoxWindowFlags() override { return ComponentPeer::windowAppearsOnTaskbar; }
    void playAlertSound() override {}
    Typeface::Ptr getTypefaceForFont (const Font& f) override;
    void drawTooltip (Graphics&, const String& text, int width, int height) override;
    void drawLabel (Graphics&, Label&) override;
    Font getLabelFont (Label&) override;
    BorderSize<int> getLabelBorderSize (Label& label) override { return label.getBorderSize(); }
    int getTabButtonSpaceAroundImage() override;
    int getTabButtonOverlap (int) override;
    int getTabButtonBestWidth (TabBarButton&, int) override;
    Rectangle<int> getTabButtonExtraComponentBounds (const TabBarButton&, Rectangle<int>&, Component&) override;
    void drawTabButton (TabBarButton&, Graphics&, bool, bool) override;
    Font getTabButtonFont (TabBarButton&, float height) override;
    void drawTabButtonText (TabBarButton&, Graphics&, bool, bool) override;
    void drawTabbedButtonBarBackground (TabbedButtonBar&, Graphics&) override;
    void drawTabAreaBehindFrontButton (TabbedButtonBar&, Graphics&, int, int) override;
    void createTabButtonShape (TabBarButton&, Path&,  bool, bool) override;
    void fillTabButtonShape (TabBarButton&, Graphics&, const Path&, bool, bool) override;
    Button* createTabBarExtrasButton() override;
    void drawComboBox (Graphics&, int, int, bool, int, int, int, int, ComboBox&) override;
    void drawButtonBackground (Graphics&, Button&, const Colour& backgroundColour, bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown) override;
    Font getTextButtonFont (TextButton&, int buttonHeight) override;
    int getTextButtonWidthToFitText (TextButton&, int buttonHeight) override;
    void drawButtonText (Graphics&, TextButton&, bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown) override;
    void drawToggleButton (Graphics&, ToggleButton&,  bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown) override;
    void changeToggleButtonWidthToFitText (ToggleButton&) override;
    void drawTickBox (Graphics&, Component&, float x, float y, float w, float h, bool ticked, bool isEnabled, bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown) override;
    void drawDrawableButton (Graphics&, DrawableButton&, bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown) override;
    void fillTextEditorBackground (Graphics&, int width, int height, TextEditor&) override;
    void drawTextEditorOutline (Graphics&, int width, int height, TextEditor&) override;
    float getCallOutBoxCornerSize (const CallOutBox&) override;

    SharedResourcePointer<SharedResources> sharedResources;

private:
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainLookAndFeel)
};
